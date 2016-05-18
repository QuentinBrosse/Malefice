#include <RakNetTypes.h>
#include "PlayerManager.h"
#include "PlayerFactory.h"
#include "PlayerInfos.h"
#include "ServerCore.h"
#include "NetworkRPC.h"
#include "Logger.h"

PlayerManager::PlayerManager() : NetworkObject(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}


void	PlayerManager::createEntity(ecs::ClientId owner)
{
	m_entities[owner] = PlayerFactory::createPlayer(owner, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), 0, 0); // TODO: pick random spawn position, set rotation/team/initial life
	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, owner, m_entities[owner]);
}

void	PlayerManager::deleteEntity(ecs::ClientId owner)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		m_entities.erase(it);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, owner);
	}

	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}


void	PlayerManager::setPlayerNickname(RakNet::RakString nickname, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(rpc->GetLastSenderAddress().systemIndex);

	if (it != m_entities.end())
	{
		ecs::PlayerInfos*	playerInfos	= dynamic_cast<ecs::PlayerInfos*>((*it->second)[ecs::AComponent::ComponentType::PLAYER_INFOS]);

		playerInfos->setNickname(nickname.C_String());
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_UPDATE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, it->second->getOwner(), it->second);
	}

	else
	{
		LOG_ERROR(ECS) << "Could not set player nickname with owner = " << rpc->GetLastSenderAddress().systemIndex << " (not found).";
	}
}
