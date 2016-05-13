#include <RakNetTypes.h>
#include "PlayerManager.h"
#include "PlayerFactory.h"
#include "ServerCore.h"
#include "NetworkRPC.h"
#include "Logger.h"

void	PlayerManager::createEntity(ecs::ClientId owner)
{
	m_entities[owner] = PlayerFactory::createPlayer(owner, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), 0, 0); // TODO: pick random spawn position, set rotation/team/initial life
	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, owner, m_entities[owner]);
}

void PlayerManager::deleteEntity(ecs::ClientId owner)
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
