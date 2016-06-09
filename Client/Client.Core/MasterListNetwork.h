#pragma once

#include <TCPInterface.h>
#include <RakSleep.h>
#include <RakString.h>
#include <vector>
#include <iostream>
#include <thread>
#include <atomic>

#include "Singleton.h"
#include "TimeUtility.h"

#include "HTTPClient.h"

class MasterListNetwork
{
	typedef void(*QueryHandler_t)(const std::vector<std::string>& servers);

	enum RefreshState
	{
		RefreshState_Ready,
		RefreshState_InProgress,
		RefreshState_UpdateRequired
	};

public:
	MasterListNetwork(QueryHandler_t handler);
	~MasterListNetwork();

	void	worker();

	bool	refresh();

	static bool	recieveHandle(const char *, unsigned int, void *);

private:

	HTTPClient*					m_httpClient;
	QueryHandler_t				m_queryHandler;
	unsigned long				m_lastRefreshTime;
	std::thread*				m_refreshThread;
	std::atomic<RefreshState>   m_refreshState;
};