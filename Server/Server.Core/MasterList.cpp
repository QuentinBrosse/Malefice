#include <iostream>
#include "MasterList.h"
#include "ProjectGlobals.h"
#include "ServerCore.h"
#include "ServerCoreConfiguration.h"
#include "PlayerManager.h"
#include "Logger.h"
#include "TimeUtility.h"
#include "StringUtility.h"

MasterList::MasterList():
	m_state(STATE_ADD), m_lastUpdateTime(0)
{
}

MasterList::~MasterList()
{
	if (m_worker.joinable())
		m_worker.join();

	if (m_tcp) {
		m_tcp->Stop();
		delete(m_tcp);
	}
}

void	MasterList::run()
{
	/*if (ServerCore::getInstance().getServerCoreConfiguration().getAddress() == "127.0.0.1")
		return;*/

	m_tcp = RakNet::OP_NEW<RakNet::TCPInterface>(__FILE__, __LINE__);
	m_tcp->Start(0, 64);

	m_worker = std::thread(&MasterList::pulse, this);
}

void	MasterList::pulse()
{
	RakNet::RakString	post;
	RakNet::Packet*		packet;

	while (ServerCore::getInstance().isActive())
	{
		if ((utility::TimeUtility::getMsTime() - m_lastUpdateTime) < 5000)
			continue;

		if (m_tcp->Connect(ProjectGlobals::MASTERLIST_URL.c_str(), 80, true) == RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			continue;

		RakSleep(100);

		if (m_state == masterListState::STATE_ADD)
			m_token = utility::StringUtility::random_string(42);

		post = RakNet::RakString::FormatForPOST(std::string(ProjectGlobals::MASTERLIST_URL).append("/api/v1/server/update").c_str(),
			"application/x-www-form-urlencoded",
			RakNet::RakString("token=%s&ip=%s&port=%d&players=%d",
				m_token.c_str(),
				ServerCore::getInstance().getServerCoreConfiguration().getAddress().c_str(),
				ServerCore::getInstance().getServerCoreConfiguration().getPort(),
				ServerCore::getInstance().getPlayerManager().getPoolSize()),
			"User-Agent: Malefice/1.0");

		m_tcp->Send(post.C_String(), post.GetLength(), m_tcp->HasCompletedConnectionAttempt(), false);

		RakSleep(1000);

		packet = m_tcp->Receive();
		if (!packet)
			continue;

		if (m_state == masterListState::STATE_ADD) {
			LOG_INFO(NETWORK) << "Server successfully posted to the MasterList";
			m_state = masterListState::STATE_UPDATE;
		}

		m_lastUpdateTime = utility::TimeUtility::getMsTime();

		m_tcp->DeallocatePacket(packet);

		RakSleep(100);
	}
}