#include <string>
#include <iostream>

#ifdef _WIN32
#include <WindowsIncludes.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

#include "MasterListNetwork.h"
#include "ProjectGlobals.h"

#include "StringUtility.h"

#include "ProjectGlobals.h"

#include "Logger.h"

MasterListNetwork::MasterListNetwork(QueryHandler_t handler, MasterList& master):
	m_queryHandler(handler),
	m_refreshState(RefreshState_Ready),
	m_refreshThread(nullptr),
	m_master(master)
{
	m_httpClient = new HTTPClient;
	m_httpClient->setReceiveHandle(&MasterListNetwork::recieveHandle, this);
	m_httpClient->setHost(ProjectGlobals::getMasterlistUrl());

	m_lastRefreshTime = utility::TimeUtility::getMsTime();
}

MasterListNetwork::~MasterListNetwork()
{
	if (m_refreshThread->joinable())
		m_refreshThread->join();

	if (m_httpClient)
		delete(m_httpClient);
}

void	MasterListNetwork::worker()
{
	while (true)
	{
		if (m_httpClient->isBusy())
		{
			m_httpClient->process();
			if (m_httpClient->gotData())
			{
				std::string* data = m_httpClient->getData();
				if (!data->empty())
				{
					std::vector<std::string> servers = utility::StringUtility::explode(data->c_str(), "<br/>");

					LOG_INFO(NETWORK) << "Discovered " << servers.size() << " server(s)";
					if (m_queryHandler)
						m_queryHandler(servers, m_master);
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
				m_refreshState = RefreshState_Ready;
			}
			else {
				LOG_DEBUG(NETWORK) << "No data got";
				std::cout << m_httpClient->getData() << std::endl;
			}
		}
		else
		{
			if (m_refreshState == RefreshState_UpdateRequired)
			{
				std::string strPath = "/api/v1/server?ordered=true";

				m_lastRefreshTime = utility::TimeUtility::getMsTime();
				m_refreshState = RefreshState_InProgress;
				m_httpClient->get(strPath);

				if (m_httpClient->getLastError() != HTTP_ERROR_NONE)
				{
					std::cout << "Failed = " << m_httpClient->getLastError() << std::endl;
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}
			}
		}
		Sleep(50);
	}
}



bool	MasterListNetwork::refresh()
{
	if (m_refreshState != RefreshState_Ready) {
		LOG_DEBUG(NETWORK) << "Worker is not ready";
		return false;
	}

	m_httpClient->reset();
	m_refreshState = RefreshState_UpdateRequired;

	if (m_refreshThread == nullptr)
	{
		m_refreshThread = new std::thread(&MasterListNetwork::worker, this);
		m_refreshThread->detach();
	} else {
		LOG_DEBUG(NETWORK) << "refreshThread not dead";
	}
	return true;
}

bool MasterListNetwork::recieveHandle(const char *, unsigned int, void *)
{
	return true;
}
