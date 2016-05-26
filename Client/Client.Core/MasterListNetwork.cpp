#include "MasterListNetwork.h"
#include "ProjectGlobals.h"

#include "StringUtility.h"

#include <string>
#include <iostream>

MasterListNetwork::MasterListNetwork() : Singleton<MasterListNetwork>(),
m_lastUpdateTime(0)
{
	m_tcp = RakNet::OP_NEW<RakNet::TCPInterface>(__FILE__, __LINE__);
	m_tcp->Start(0, 64);
}

MasterListNetwork::~MasterListNetwork()
{
	if (m_tcp) {
		if (m_tcp->WasStarted())
			m_tcp->Stop();
		delete(m_tcp);
	}
}

std::vector<std::string>	MasterListNetwork::fetch()
{
	RakNet::RakString			post;
	RakNet::Packet*				packet;
	std::vector<std::string>	retn;

	if ((utility::TimeUtility::getMsTime() - m_lastUpdateTime) < 3000)
		return retn;

	if (m_tcp->Connect(ProjectGlobals::MASTERLIST_URL.c_str(), 80, true) == RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		return retn;

	RakSleep(100);

	post = RakNet::RakString::FormatForGET(std::string(ProjectGlobals::MASTERLIST_URL).append("/api/v1/server?ordered=true").c_str(), "User-Agent: Malefice/1.0");

	m_tcp->Send(post.C_String(), post.GetLength(), m_tcp->HasCompletedConnectionAttempt(), false);

	RakSleep(1000);

	packet = m_tcp->Receive();
	if (!packet)
		return retn;

	std::vector<std::string> strings = utility::StringUtility::explode(std::string((char *)packet->data), "\r\n");
	std::cout << strings[15] << std::endl;

	m_lastUpdateTime = utility::TimeUtility::getMsTime();
	m_tcp->DeallocatePacket(packet);

	return retn;
}