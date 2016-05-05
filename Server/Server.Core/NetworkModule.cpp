#include <iostream>
#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "GeneralRPC.h"
#include "PlayerRPC.h"
#include "ProjectGlobals.h"

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


bool	NetworkModule::init(const std::string& address, short port, const std::string& password)
{
	RakNet::SocketDescriptor	descriptor(port, address.c_str());

	if (m_rakPeer->Startup(ProjectGlobals::MAX_PLAYERS_NB, &descriptor, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		m_rakPeer->SetMaximumIncomingConnections(ProjectGlobals::MAX_PLAYERS_NB);
		m_rakPeer->SetTimeoutTime(10000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
		if (password.length() > 0)
			m_rakPeer->SetIncomingPassword(password.c_str(), password.length());
	}
	else
	{
		return false;
	}
	return true;
}

void	NetworkModule::pulse()
{
	RakNet::Packet*	packet = nullptr;

	while (packet = m_rakPeer->Receive())
	{
		switch (packet->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
				LOG_INFO << "[network] : Incoming connection from " << packet->systemAddress.ToString(true, ':');
				break;
			case ID_DISCONNECTION_NOTIFICATION:
				LOG_INFO << "[network] : PlayerId " << packet->systemAddress.systemIndex << " disconnected";
				break;
			case ID_CONNECTION_LOST:
				LOG_INFO << "[network] : PlayerId " << packet->systemAddress.systemIndex << " lost";
				break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}


void	NetworkModule::callRPC(const std::string& rpc, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, int playerId, bool broadcast)
{
	if (m_rpc != nullptr)
		m_rpc->Call(rpc.c_str(), bitStream, packetPriority, packetReliability, 0, m_rakPeer->GetSystemAddressFromIndex(playerId), broadcast);
}


RakNet::RakPeerInterface*	NetworkModule::getRakPeer()
{
	return m_rakPeer;
}

RakNet::RPC4*	NetworkModule::getRPC()
{
	return m_rpc;
}
