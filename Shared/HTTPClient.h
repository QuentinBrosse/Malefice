#pragma once

#include	<string>
#include	<map>

#include "Export.h"

#define DEFAULT_CONTENT_TYPE	"text/plain"
#define	TIMEOUT					30000

#ifndef _WIN32
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif

typedef void(*HeaderHandler_t)(unsigned int uiStatus, unsigned int uiContentLength, void * pUserData);
typedef bool(*RecieveHandler_t)(const char * szData, unsigned int uiDataSize, void * pUserData);
typedef void(*FileWriteHandler_t)(unsigned int uiDataSize, void * pUserData);

// Status codes
enum eHttpStatus
{
	HTTP_STATUS_NONE,
	HTTP_STATUS_INVALID,
	HTTP_STATUS_GET_DATA,
	HTTP_STATUS_GOT_DATA
};

// Error codes
enum eHttpError
{
	HTTP_ERROR_NONE,
	HTTP_ERROR_SOCKET_PREPARE_FAILED,
	HTTP_ERROR_INVALID_HOST,
	HTTP_ERROR_IOCTL_FAILED,
	HTTP_ERROR_CONNECTION_FAILED,
	HTTP_ERROR_SEND_FAILED,
	HTTP_ERROR_REQUEST_TIMEOUT,
	HTTP_ERROR_NO_HEADER
};

class MALEFICE_DLL_EXPORT HTTPClient
{

private:

	int									m_socket;
	long								m_receiveTimeout;
	bool								m_connected;
	std::string							m_host;
	unsigned short						m_port;
	eHttpStatus							m_status;
	std::map<std::string, std::string >	m_headerMap;
	std::string							m_data;
	eHttpError							m_lastError;
	std::string							m_userAgent;
	std::string							m_referer;
	unsigned long						m_requestStart;
	bool								m_parseHeaders;

	HeaderHandler_t						m_headerHandler;
	void*								m_headerHandlerUserData;

	RecieveHandler_t					m_recieveHandler;
	void*								m_recieveHandlerUserData;

	FILE*								m_file;
	FileWriteHandler_t					m_fileWriteHandler;
	void*								m_fileWriteUserData;

	void								resetVars(void);
	bool								Connect(void);
	void								Disconnect(void);
	bool								parseHeaders(std::string& strBuffer, int& iBufferSize);
	bool								write(const std::string& szData, int iLen);
	int									read(const std::string& szBuffer, int iLen);

public:

	HTTPClient(void);
	~HTTPClient(void);

	virtual void					setReceiveTimeout(long lReceiveTimeout);
	virtual long					getReceiveTimeout(void) { return m_receiveTimeout; }
	virtual bool					isConnected(void) { return m_connected; }
	virtual bool					isInvalid(void) { return (m_status == HTTP_STATUS_INVALID); }
	virtual bool					gettingData(void) { return (m_status == HTTP_STATUS_GET_DATA); }
	virtual bool					gotData(void) { return (m_status == HTTP_STATUS_GOT_DATA); }
	virtual bool					isBusy(void) { return (m_status == HTTP_STATUS_GET_DATA); }
	virtual std::string				* getData(void) { return &m_data; }
	virtual eHttpError				getLastError(void) { return m_lastError; }
	virtual void					setUserAgent(std::string strUserAgent) { m_userAgent = strUserAgent; }
	virtual std::string				getUserAgent(void) { return m_userAgent; }
	virtual void					setReferer(std::string strReferer) { m_referer = strReferer; }
	virtual std::string				getReferer(void) { return m_referer; }
	virtual void					setHost(std::string strHost) { m_host = strHost; }
	virtual std::string				getHost(void) { return m_host; }
	virtual void					setPort(unsigned short usPort) { m_port = usPort; }
	virtual unsigned short			getPort(void) { return m_port; }
	virtual bool					get(const std::string& strPath);
	virtual bool					post(bool bHasResponse, std::string strPath, std::string strData = "", std::string strContentType = DEFAULT_CONTENT_TYPE);
	virtual void					process(void);
	virtual std::string				getLastErrorString(void);

	virtual void					setHeaderHandler(HeaderHandler_t pfnHeaderHandler, void * pHeaderHandlerUserData) { m_headerHandler = pfnHeaderHandler; m_headerHandlerUserData = pHeaderHandlerUserData; }
	virtual void					setReceiveHandle(RecieveHandler_t pfnRecieveHandler, void * pRecieveHandlerUserData) { m_recieveHandler = pfnRecieveHandler; m_recieveHandlerUserData = pRecieveHandlerUserData; }
	virtual void					reset(void);

	virtual void					shouldParseHeaders(bool bShould) { m_parseHeaders = bShould; }

	virtual	void					setFile(FILE * file = NULL) { m_file = file; }
	virtual void					setFileWriteHandler(FileWriteHandler_t pfnFileWriteHandler, void * pFileWriteUserData) { m_fileWriteHandler = pfnFileWriteHandler; m_fileWriteUserData = pFileWriteUserData; }

};