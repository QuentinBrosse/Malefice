#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "GeneralRPC.h"
#include "PlayerRPC.h"
#include "ProjectGlobals.h"
#include "ServerCore.h"
#include "PlayerManager.h"
#include "Logger.h"

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_rpc(RakNet::RPC4::GetInstance())
{
	m_rakPeer->AttachPlugin(m_rpc);
	GeneralRPC::registerRPC(m_rpc);
	PlayerRPC::registerRPC(m_rpc);
}

NetworkModule::~NetworkModule()
{
	m_rakPeer->Shutdown(500);
	GeneralRPC::unregisterRPC(m_rpc);
	PlayerRPC::unregisterRPC(m_rpc);
	m_rakPeer->DetachPlugin(m_rpc);
	RakNet::RPC4::DestroyInstance(m_rpc);
	RakNet::RakPeerInterface::DestroyInstance(m_rakPeer);
}


bool	NetworkModule::init(const std::string& address, unsigned short port, const std::string& password)
{
	RakNet::SocketDescriptor	descriptor(port, address.c_str());

	if (m_rakPeer->Startup(ProjectGlobals::MAX_PLAYERS_NB, &descriptor, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		m_rakPeer->SetMaximumIncomingConnections(ProjectGlobals::MAX_PLAYERS_NB);
		m_rakPeer->SetTimeoutTime(10000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		if (password.length() > 0)
			m_rakPeer->SetIncomingPassword(password.c_str(), password.length());
		return true;
	}
	else
	{
		return false;
	}
}

void	NetworkModule::pulse()
{
	RakNet::Packet*	packet = nullptr;

	while (packet = m_rakPeer->Receive())
	{
		switch (packet->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
				LOG_INFO(NETWORK) << "Incoming connection from " << packet->systemAddress.ToString(true, ':') << ".";
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				if (ServerCore::getInstance().getPlayerManager()->hasPlayer(static_cast<ecs::NetworkID>(packet->systemAddress.systemIndex)))
				{
					ServerCore::getInstance().getPlayerManager()->removePlayer(static_cast<ecs::NetworkID>(packet->systemAddress.systemIndex));
					LOG_INFO(NETWORK) << "Player " << packet->systemAddress.systemIndex << " disconnected" << ".";
				}
				break;
			case ID_CONNECTION_LOST:
				if (ServerCore::getInstance().getPlayerManager()->hasPlayer(static_cast<ecs::NetworkID>(packet->systemAddress.systemIndex)))
				{
					ServerCore::getInstance().getPlayerManager()->removePlayer((ecs::NetworkID)packet->systemAddress.systemIndex);
					LOG_WARNING(NETWORK) << "Player " << packet->systemAddress.systemIndex << " disconnected (connection lost)" << ".";
				}
				break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}


void	NetworkModule::callRPC(const std::string& rpc, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, int playerId, bool broadcast)
{
	if (m_rpc != nullptr)
		m_rpc->Call(rpc.c_str(), bitStream, packetPriority, packetReliability, 0, m_rakPeer->GetSystemAddressFromIndex(playerId), broadcast);
	else
		LOG_ERROR(NETWORK) << "RPC null pointer";
}
