#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "NetworkManager.h"
#include "NetworkRPC.h"
#include "ServerCore.h"
#include "RakNetUtility.h"
#include "ProjectGlobals.h"
#include "Logger.h"

const RakNet::TimeMS	NetworkModule::TIMEOUT_MS			= 10000;
const RakNet::TimeMS	NetworkModule::SHUTDOWN_TIMEOUT_MS	= 500;

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_rpc()
{
	m_rpc.SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
	this->registerRPCs();
	m_rakPeer->AttachPlugin(&m_rpc);
}

NetworkModule::~NetworkModule()
{
	m_rakPeer->Shutdown(NetworkModule::SHUTDOWN_TIMEOUT_MS);
	m_rakPeer->DetachPlugin(&m_rpc);
	this->unregisterRPCs();
	RakNet::RakPeerInterface::DestroyInstance(m_rakPeer);
}


bool	NetworkModule::init(const std::string& address, unsigned short port, const std::string& password)
{
	RakNet::SocketDescriptor	descriptor(port, address.c_str());
	
	if (m_rakPeer->Startup(ProjectGlobals::MAX_PLAYERS_NB, &descriptor, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		m_rakPeer->SetMaximumIncomingConnections(ProjectGlobals::MAX_PLAYERS_NB);
		m_rakPeer->SetTimeoutTime(NetworkModule::TIMEOUT_MS, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
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
	
	while ((packet = m_rakPeer->Receive()) != nullptr)
	{
		switch (packet->data[0])
		{
		case DefaultMessageIDTypes::ID_NEW_INCOMING_CONNECTION:
			this->acceptClient(packet);
			break;
		case DefaultMessageIDTypes::ID_DISCONNECTION_NOTIFICATION:
			ServerCore::getInstance().getPlayerManager().deleteEntity(packet->systemAddress.systemIndex);
			LOG_INFO(NETWORK) << "Client with ID = " << packet->systemAddress.systemIndex << " disconnected.";
			break;
		case DefaultMessageIDTypes::ID_CONNECTION_LOST:
			ServerCore::getInstance().getPlayerManager().deleteEntity(packet->systemAddress.systemIndex);
			LOG_WARNING(NETWORK) << "Client with ID = " << packet->systemAddress.systemIndex << " lost connection.";
			break;
		case DefaultMessageIDTypes::ID_RPC_REMOTE_ERROR:
			RakNetUtility::logRPCRemoteError(static_cast<RakNet::RPCErrorCodes>(packet->data[1]), std::string(reinterpret_cast<char*>(packet->data) + 2));
			break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}


void	NetworkModule::registerRPCs()
{
	m_rpc.RegisterFunction(NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME.c_str(), &PlayerManager::setPlayerNickname);
	m_rpc.RegisterFunction(NetworkRPC::PLAYER_MANAGER_SERVER_UPDATE_ENTITY.c_str(), &PlayerManager::updateEntity);
}

void	NetworkModule::unregisterRPCs()
{
	m_rpc.UnregisterFunction(NetworkRPC::PLAYER_MANAGER_SET_PLAYER_NICKNAME.c_str());
	m_rpc.UnregisterFunction(NetworkRPC::PLAYER_MANAGER_SERVER_UPDATE_ENTITY.c_str());
}


void	NetworkModule::acceptClient(RakNet::Packet* packet)
{
	this->callRPC(NetworkRPC::CLIENT_CORE_SET_CLIENT_ID, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::ClientCore), packet->systemAddress, false, packet->systemAddress.systemIndex);
	ServerCore::getInstance().getPlayerManager().createEntity(packet->systemAddress.systemIndex);
	LOG_INFO(NETWORK) << "New client connected from " << packet->systemAddress.ToString(true, ':') << ", assigned clientId = " << packet->systemAddress.systemIndex << ".";
}
