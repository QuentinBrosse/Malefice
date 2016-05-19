#include "PlayerManager.h"
#include "ClientCore.h"
#include "PlayerFactory.h"
#include "PositionSystem.h"
#include "WeaponManagerSystem.h"

PlayerManager::PlayerManager() : EntityManager(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}


void	PlayerManager::addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	ecs::Entity*	localEntity = new ecs::Entity(*entity);

	EntityManager::addEntity(owner, localEntity, rpc);

	if (ClientCore::getInstance().getClientId() == owner)
	{
		this->setCurrentPlayer(localEntity);
		
	}
}

void	PlayerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);
}

void	PlayerManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	EntityManager::removeEntity(owner, rpc);
}


void PlayerManager::initPlayersScene()
{
	for (auto player : m_entities)
	{
		PlayerFactory::initScene(GraphicUtil::getInstance().getDevice(), "sydney.bmp", "sydney.md2", *player.second);
		ecs::PositionSystem::initScenePosition(*player.second);
	}
}

ecs::Entity*	PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}

void PlayerManager::setCurrentPlayer(ecs::Entity * localPlayer)
{
	m_currentPlayer = localPlayer;
}
