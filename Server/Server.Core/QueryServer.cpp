#include <thread>
#include <chrono>

#include "QueryServer.h"

#include "ServerCore.h"
#include "ServerCoreConfiguration.h"
#include "PlayerManager.h"

#include "Logger.h"

const char * GetIPFromSocketAddress(int af, const void * src, char * dst, int cnt)
{
	if (af == AF_INET || af == PF_INET)
	{
		sockaddr_in in;
		memset(&in, 0, sizeof(in));
		in.sin_family = af;
		memcpy(&in.sin_addr, src, sizeof(in_addr));
		getnameinfo((sockaddr *)&in, sizeof(sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
		return dst;
	}
	else if (af == AF_INET6 || af == PF_INET6)
	{
		struct sockaddr_in6 in;
		memset(&in, 0, sizeof(in));
		in.sin6_family = af;
		memcpy(&in.sin6_addr, src, sizeof(in.sin6_addr));
		getnameinfo((sockaddr *)&in, sizeof(sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
		return dst;
	}

	return NULL;
}

QueryServer::~QueryServer()
{
	if (m_worker.joinable())
		m_worker.join();

	if (m_socket != -1)
		closesocket(m_socket);
#ifdef WIN32
	WSACleanup();
#endif
}

void	QueryServer::init(unsigned short port)
{
#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	sockaddr_in address;
	memset(&address, 0, sizeof(sockaddr_in));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);

	if (strlen(ServerCore::getInstance().getServerCoreConfiguration().getAddress().c_str()) > 0)
#ifdef WIN32
		InetPton(m_socket, ServerCore::getInstance().getServerCoreConfiguration().getAddress().c_str(), &address.sin_addr.s_addr);
#else
		inet_pton(m_socket, ServerCore::getInstance().getServerCoreConfiguration().getAddress().c_str(), &address.sin_addr.s_addr);
#endif

	m_socket = socket(AF_INET, SOCK_DGRAM, 0);

#ifdef WIN32
	unsigned long sockopt = 1;
	ioctlsocket(m_socket, FIONBIO, &sockopt);
#else
	fcntl(m_socket, F_SETFL, fcntl(m_socket, F_GETFL) | O_NONBLOCK);
#endif

	if (bind(m_socket, (sockaddr *)&address, sizeof(sockaddr_in)) == -1)
		LOG_ERROR(NETWORK) << "Failed to bind the query address";

	m_worker = std::thread(&QueryServer::worker, this);
}

std::string QueryServer::reply()
{
	std::stringstream reply;
	reply << "Malefice";

	//Nom de serveur
	reply << (unsigned char)(ServerCore::getInstance().getServerCoreConfiguration().getAddress().length() + 1);
	reply << ServerCore::getInstance().getServerCoreConfiguration().getAddress().c_str();

	//Mot de passe ?
	reply << (unsigned char)(ServerCore::getInstance().getServerCoreConfiguration().getPassword().length() > 0 ? 1 : 0);

	//Nombre de joueurs
	std::string players("%d", ServerCore::getInstance().getPlayerManager().getPoolSize());
	reply << (unsigned char)(players.length());
	reply << players.c_str();

	return reply.str();
}

void	QueryServer::worker()
{
	while (ServerCore::getInstance().isActive())
	{
		static char buffer[1024];
		memset(buffer, 0, sizeof(buffer));

		sockaddr_in address;
		memset(&address, 0, sizeof(sockaddr_in));
		int fromLength = sizeof(sockaddr_in);
		
		int readBytes = -1;
		while ((readBytes = recvfrom(m_socket, buffer, sizeof(buffer), NULL, (sockaddr *)&address, (socklen_t *)&fromLength)) != -1)
		{
			char ipAddress[64];
			GetIPFromSocketAddress(address.sin_family, &address.sin_addr, ipAddress, sizeof(ipAddress));

			unsigned short port = ntohs(address.sin_port);
			if (strcmp(buffer, "Malefice") == 0)
			{
				std::string reply = this->reply();
				sendto(m_socket, reply.c_str(), reply.length(), NULL, (sockaddr *)&address, sizeof(sockaddr_in));
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

int	QueryServer::getSocket() const
{
	return m_socket;
}
