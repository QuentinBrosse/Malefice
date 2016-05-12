#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "ProjectGlobals.h"
#include "ServerCore.h"
#include "RakNetUtility.h"
#include "NetworkManager.h"
#include "Logger.h"

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_rpc(new RakNet::RPC3()), m_generalRPC(nullptr), m_playerRPC(nullptr)
{
	m_rpc->SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
	m_rakPeer->AttachPlugin(m_rpc);
}

NetworkModule::~NetworkModule()
{
	delete m_generalRPC;
	delete m_playerRPC;
	m_rakPeer->DetachPlugin(m_rpc);
	m_rakPeer->Shutdown(500);
	delete m_rpc;
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
		m_generalRPC = new GeneralRPC();
		m_playerRPC = new PlayerRPC();
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
				if (ServerCore::getInstance().getPlayerManager().hasPlayer(static_cast<ecs::PlayerId>(packet->systemAddress.systemIndex)))
				{
					ServerCore::getInstance().getPlayerManager().removePlayer(static_cast<ecs::PlayerId>(packet->systemAddress.systemIndex));
					LOG_INFO(NETWORK) << "Player " << packet->systemAddress.systemIndex << " disconnected" << ".";
				}
				break;
			case ID_CONNECTION_LOST:
				if (ServerCore::getInstance().getPlayerManager().hasPlayer(static_cast<ecs::PlayerId>(packet->systemAddress.systemIndex)))
				{
					ServerCore::getInstance().getPlayerManager().removePlayer((ecs::PlayerId)packet->systemAddress.systemIndex);
					LOG_WARNING(NETWORK) << "Player " << packet->systemAddress.systemIndex << " disconnected (connection lost)" << ".";
				}
				break;
			case ID_RPC_REMOTE_ERROR:
				RakNetUtility::logRPCRemoteError(static_cast<RakNet::RPCErrorCodes>(packet->data[1]), std::string(reinterpret_cast<char*>(packet->data) + 2));
				break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}


void	NetworkModule::callRPC(const std::string& rpc, RakNet::NetworkIDObject* object, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, RakNet::SystemAddress to, bool broadcast)
{
	RakNet::RPC3::CallExplicitParameters	callExplicitParameters(object->GetNetworkID(), to, broadcast, 0, packetPriority, packetReliability, 0);

	if (m_rpc != nullptr)
		m_rpc->CallExplicit(rpc.c_str(), &callExplicitParameters, bitStream, m_rpc);
	else
		LOG_ERROR(NETWORK) << "RPC null pointer";
}



RakNet::RPC3*	NetworkModule::getRPC()
{
	return m_rpc;
}
