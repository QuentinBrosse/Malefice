#include	"HTTPClient.h"

#ifdef _WIN32
#include <winsock2.h>
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define closesocket close
#include <string.h>
#include <unistd.h>
#endif

#include "Logger.h"

#include "StringUtility.h"
#include "TimeUtility.h"

#define MAX_BUFFER				8192
#define DEFAULT_PORT			80
#define DEFAULT_USER_AGENT		"Malefice/1.0"
#define DEFAULT_REFERER			"http://malefice.pinot.ovh"

HTTPClient::HTTPClient()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	m_socket = INVALID_SOCKET;

	resetVars();
}

HTTPClient::~HTTPClient()
{
	if (m_connected)
		Disconnect();

#ifdef _WIN32
	WSACleanup();
#endif
}

void HTTPClient::resetVars()
{
	m_receiveTimeout = 1;
	m_connected = false;
	m_host.clear();
	m_port = DEFAULT_PORT;
	m_status = HTTP_STATUS_NONE;
	m_headerMap.clear();
	m_data.clear();
	m_lastError = HTTP_ERROR_NONE;
	m_userAgent = DEFAULT_USER_AGENT;
	m_referer = DEFAULT_REFERER;
	m_requestStart = 0;
	m_parseHeaders = true;
	m_recieveHandler = NULL;
	m_recieveHandlerUserData = NULL;
	m_headerHandler = NULL;
	m_fileWriteHandler = NULL;
	m_fileWriteUserData = NULL;
	m_file = NULL;
}

void HTTPClient::setReceiveTimeout(long receiveTimeout)
{
	m_receiveTimeout = receiveTimeout;
}

bool HTTPClient::Connect()
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (m_socket == INVALID_SOCKET)
	{
		m_lastError = HTTP_ERROR_SOCKET_PREPARE_FAILED;
		return false;
	}

	hostent * heHost = gethostbyname(m_host.c_str());

	if (heHost == NULL)
	{
		m_lastError = HTTP_ERROR_INVALID_HOST;
		return false;
	}

	sockaddr_in sinAddress;
	sinAddress.sin_family = AF_INET;
	sinAddress.sin_port = htons(m_port);
	sinAddress.sin_addr = *((in_addr *)heHost->h_addr);
	memset(&sinAddress.sin_zero, 0, (sizeof(char) * 8));

	if (connect(m_socket, (sockaddr *)&sinAddress, sizeof(sockaddr)) < 0)
	{
		Disconnect();

		m_lastError = HTTP_ERROR_CONNECTION_FAILED;
		return false;
	}
	m_connected = true;
	return true;
}

void HTTPClient::Disconnect()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	m_connected = false;
}

bool HTTPClient::write(const std::string& szData, int iLen)
{
	if (send(m_socket, szData.c_str(), iLen, 0) == SOCKET_ERROR)
	{
		m_lastError = HTTP_ERROR_SEND_FAILED;
		return false;
	}

	return true;
}

int HTTPClient::read(const std::string& szBuffer, int iLen)
{
	return recv(m_socket, const_cast<char *>(szBuffer.c_str()), iLen, 0);
}

bool HTTPClient::get(const std::string& strPath)
{
	if (!Connect())
		return false;

	m_headerMap.clear();
	m_data.clear();

	std::string strGet = utility::StringUtility::string_format("GET %s HTTP/1.0\r\n"
		"Host: %s\r\n"
		"User-Agent: %s\r\n"
		"Referer: %s\r\n"
		"Connection: close\r\n"
		"\r\n",
		strPath.c_str(), m_host.c_str(), m_userAgent.c_str(),
		m_referer.c_str());

	if (!write(strGet.c_str(), strGet.length()))
		return false;

	m_status = HTTP_STATUS_GET_DATA;

	m_requestStart = utility::TimeUtility::getMsTime();
	return true;
}

bool HTTPClient::post(bool hasResponse, std::string strPath, std::string strData, std::string strContentType)
{
	if (!Connect())
		return false;

	m_headerMap.clear();
	m_data.clear();

	std::string strPost = utility::StringUtility::string_format("POST %s HTTP/1.0\r\n" \
		"Host: %s\r\n" \
		"User-Agent: %s\r\n\r\n" \
		"Referer: %s\r\n" \
		"Content-Type: %s\r\n" \
		"Content-Length: %d\r\n" \
		"Connection: close\r\n" \
		"\r\n" \
		"%s",
		strPath.c_str(), m_host.c_str(), m_userAgent.c_str(),
		m_referer.c_str(), strContentType.c_str(), strData.length(),
		strData.c_str());

	if (!write(strPost.c_str(), strPost.length()))
		return false;

	if (hasResponse)
	{
		m_status = HTTP_STATUS_GET_DATA;

		m_requestStart = utility::TimeUtility::getMsTime();
	}
	else
	{
		Disconnect();
	}

	return true;
}

bool HTTPClient::parseHeaders(std::string& strBuffer, int& iBufferSize)
{
	if (m_parseHeaders)
	{
		std::string headers = strBuffer;

		std::string strStatus = headers;
		strStatus.erase(0, 9);
		strStatus.erase(12, strStatus.length());
		unsigned int uiStatus = stoi(strStatus);

		size_t sOff = headers.find("Content-Length:");

		if (sOff != std::string::npos)
		{
			headers.erase(0, sOff + 16);
			sOff = headers.find("Connection:");

			if (sOff != std::string::npos)
				headers.erase(sOff, headers.length());
		}

		if (m_headerHandler)
			m_headerHandler(uiStatus, static_cast<unsigned int>(stoi(headers)), m_headerHandlerUserData);
	}

	int iHeaderSize = 0;
	for (int i = 0; i < iBufferSize; i++)
	{
		if (strBuffer.at(i) == '\r' && strBuffer.at(i + 1) == '\n' && strBuffer.at(i + 2) == '\r' && strBuffer.at(i + 3) == '\n')
		{
			iHeaderSize = i + 4;
			break;
		}
	}

	if (iHeaderSize > 0)
	{
		iBufferSize -= iHeaderSize;
		strBuffer.erase(0, iHeaderSize);
	}
	m_headerMap["HeaderSize"] = iHeaderSize;
	return true;
}

void HTTPClient::process()
{
	if (m_requestStart > 0 && (utility::TimeUtility::getMsTime() - m_requestStart) >= TIMEOUT)
	{
		m_status = HTTP_STATUS_NONE;
		m_lastError = HTTP_ERROR_REQUEST_TIMEOUT;
		m_requestStart = 0;
		Disconnect();
		return;
	}

	if (m_status != HTTP_STATUS_NONE)
	{
		switch (m_status)
		{
		case HTTP_STATUS_GET_DATA:
		{
			char szBuffer[MAX_BUFFER];
			memset(szBuffer, 0, sizeof(szBuffer));

			int iBytesRead = read(szBuffer, sizeof(szBuffer));
			int iSkipBytes = 0;

			if (iBytesRead > 0)
			{
				std::string strBuffer;
				strBuffer.assign(szBuffer, iBytesRead);

				if (m_headerMap.empty())
				{
					iSkipBytes = iBytesRead;

					if (!parseHeaders(strBuffer, iBytesRead))
					{
						m_status = HTTP_STATUS_INVALID;
						m_lastError = HTTP_ERROR_NO_HEADER;

						m_requestStart = 0;
						Disconnect();

						LOG_ERROR(NETWORK) << "HTTP DATA READ ERROR - No headers.";

						return;
					}

					iSkipBytes -= iBytesRead;
					if (iBytesRead == 0)
						return;
				}

				char * szData = (iBytesRead ? (szBuffer + iSkipBytes) : NULL);

				if (m_recieveHandler != NULL)
				{
					if (m_recieveHandler(szData, iBytesRead, m_recieveHandlerUserData))
						m_data.append(szData, iBytesRead);
				}
				else if (m_file != NULL)
				{
					fwrite(szData, 1, iBytesRead, m_file);
					if (m_fileWriteHandler)
						m_fileWriteHandler(iBytesRead, m_fileWriteUserData);
				}
				else
					m_data.append(szData, iBytesRead);
			}
			else
			{
				m_status = HTTP_STATUS_GOT_DATA;
				m_requestStart = 0;
				Disconnect();
			}
		}
		break;
		}
	}
}

std::string HTTPClient::getLastErrorString()
{
	std::string strError("Unknown");

	switch (GetLastError())
	{
	case HTTP_ERROR_SOCKET_PREPARE_FAILED:
		strError = ("Failed to prepare socket");
		break;
	case HTTP_ERROR_INVALID_HOST:
		strError = ("Invalid host");
		break;
	case HTTP_ERROR_IOCTL_FAILED:
		strError = ("IoCtl failed");
		break;
	case HTTP_ERROR_CONNECTION_FAILED:
		strError = ("Connection failed");
		break;
	case HTTP_ERROR_SEND_FAILED:
		strError = ("Send failed");
		break;
	case HTTP_ERROR_REQUEST_TIMEOUT:
		strError = ("Request timed out");
		break;
	case HTTP_ERROR_NO_HEADER:
		strError = ("No header");
		break;
	}

	return strError;
}

void HTTPClient::reset()
{
	if (isConnected())
	{
		Disconnect();
	}
	m_status = HTTP_STATUS_NONE;
	setFile();
}