#include <RPC3.h>
#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "RakNetUtility.h"
#include "NetworkManager.h"
#include "NetworkRPC.h"
#include "ClientCore.h"
#include "LifeSystem.h"
#include "Logger.h"
#include "WeaponSystem.h"

#ifndef THREAD_PRIORITY_NORMAL
# define THREAD_PRIORITY_NORMAL 0
#endif

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_serverAddress(), m_connectionState(RakNet::ConnectionState::IS_NOT_CONNECTED), m_rpc()
{
  m_rpc.SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
  this->registerRPCs();
  m_rakPeer->AttachPlugin(&m_rpc);
}

NetworkModule::~NetworkModule()
{
  m_rakPeer->DetachPlugin(&m_rpc);
  this->unregisterRPCs();
  m_rakPeer->Shutdown(500);
  RakNet::RakPeerInterface::DestroyInstance(m_rakPeer);
}


bool	NetworkModule::init()
{
  RakNet::SocketDescriptor	sd{};

  if (m_rakPeer->Startup(1, &sd, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
    {
      return true;
    }

  else
    {
      return false;
    }
}

bool	NetworkModule::connect(const std::string& address, unsigned short port, const std::string& password)
{
  if (m_connectionState != RakNet::ConnectionState::IS_NOT_CONNECTED && m_connectionState == RakNet::ConnectionState::IS_DISCONNECTED)
    return true;
  if (m_rakPeer->Connect(address.c_str(), port, password.c_str(), password.length()) == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
    {
      m_connectionState = RakNet::ConnectionState::IS_CONNECTING;
      return true;
    }
  else
    {
      m_connectionState = RakNet::ConnectionState::IS_NOT_CONNECTED;
      return false;
    }
}

void	NetworkModule::disconnect()
{
  if (this->getConnectionState() != RakNet::ConnectionState::IS_CONNECTED)
    return;
  m_rakPeer->CloseConnection(m_serverAddress, true);
  m_connectionState = RakNet::ConnectionState::IS_DISCONNECTED;
}

void	NetworkModule::pulse()
{
  RakNet::Packet*	packet = nullptr;

	if (m_connectionState != RakNet::ConnectionState::IS_CONNECTED && m_connectionState != RakNet::ConnectionState::IS_CONNECTING)
		return;
	while ((packet = m_rakPeer->Receive()) != nullptr)
	{
		switch (packet->data[0])
		{
		case DefaultMessageIDTypes::ID_CONNECTION_REQUEST_ACCEPTED:
			m_serverAddress = packet->systemAddress;
			m_connectionState = RakNet::ConnectionState::IS_CONNECTED;
			break;
		case DefaultMessageIDTypes::ID_DISCONNECTION_NOTIFICATION:
			m_connectionState = RakNet::ConnectionState::IS_DISCONNECTED;
			break;
		case DefaultMessageIDTypes::ID_CONNECTION_LOST:
			m_connectionState = RakNet::ConnectionState::IS_DISCONNECTED;
			break;
		case DefaultMessageIDTypes::ID_RPC_REMOTE_ERROR:
			RakNetUtility::logRPCRemoteError(static_cast<RakNet::RPCErrorCodes>(packet->data[1]), std::string(reinterpret_cast<char*>(packet->data) + 2));
			break;
		}
		m_rakPeer->DeallocatePacket(packet);
		}
}

RakNet::ConnectionState	NetworkModule::getConnectionState()	const
{
  return m_connectionState;
}



void	NetworkModule::registerRPCs()
{
	m_rpc.RegisterFunction(NetworkRPC::CLIENT_CORE_SET_CLIENT_ID.c_str(), &ClientCore::setClientId);
	m_rpc.RegisterFunction(NetworkRPC::CLIENT_CORE_NOTIFY_INVALID_NICKNAME.c_str(), &ClientCore::notifyInvalidNickname);
	m_rpc.RegisterFunction(NetworkRPC::CLIENT_CORE_START_GAME.c_str(), &ClientCore::startGame);
	m_rpc.RegisterFunction(NetworkRPC::CLIENT_CORE_STOP_GAME.c_str(), &ClientCore::stopGame);
	m_rpc.RegisterFunction(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY.c_str(), &PlayerManager::addEntity);
	m_rpc.RegisterFunction(NetworkRPC::PLAYER_MANAGER_UPDATE_ENTITY.c_str(), &PlayerManager::updateEntity);
	m_rpc.RegisterFunction(NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY.c_str(), &PlayerManager::removeEntity);
	m_rpc.RegisterFunction(NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY.c_str(), &SpawnerManager::addEntity);
	m_rpc.RegisterFunction(NetworkRPC::SPAWNER_MANAGER_UPDATE_ENTITY.c_str(), &SpawnerManager::updateEntity);
	m_rpc.RegisterFunction(NetworkRPC::SPAWNER_MANAGER_REMOVE_ENTITY.c_str(), &SpawnerManager::removeEntity);
	m_rpc.RegisterFunction(NetworkRPC::SPAWNER_MANAGER_SET_VISIBILITY.c_str(), &SpawnerManager::setSpawnerVisibility);
	m_rpc.RegisterFunction(NetworkRPC::LIFE_SYSTEM_DIE.c_str(), &LifeSystem::die);
	m_rpc.RegisterFunction(NetworkRPC::LIFE_SYSTEM_KILL.c_str(), &LifeSystem::kill);
	m_rpc.RegisterFunction(NetworkRPC::TRIGGER_SHOOT_ACTIONS.c_str(), &ecs::WeaponSystem::triggerShootActions);
}

void	NetworkModule::unregisterRPCs()
{
  m_rpc.UnregisterFunction(NetworkRPC::CLIENT_CORE_SET_CLIENT_ID.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::CLIENT_CORE_NOTIFY_INVALID_NICKNAME.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::CLIENT_CORE_START_GAME.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::CLIENT_CORE_STOP_GAME.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::PLAYER_MANAGER_UPDATE_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::SPAWNER_MANAGER_UPDATE_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::SPAWNER_MANAGER_REMOVE_ENTITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::SPAWNER_MANAGER_SET_VISIBILITY.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::LIFE_SYSTEM_DIE.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::LIFE_SYSTEM_KILL.c_str());
  m_rpc.UnregisterFunction(NetworkRPC::TRIGGER_SHOOT_ACTIONS.c_str());
}
