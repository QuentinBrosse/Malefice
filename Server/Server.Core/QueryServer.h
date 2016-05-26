#pragma once

#include <thread>
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

#include "Singleton.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

class QueryServer: public Singleton<QueryServer>
{
private:
	std::thread		m_worker;
	int				m_socket;

	void			worker();
	std::string		reply();

public:
	QueryServer() = default;
	~QueryServer();

	void			init(unsigned short port);

	int				getSocket() const;
};