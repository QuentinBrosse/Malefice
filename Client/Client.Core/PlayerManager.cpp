#include "PlayerManager.h"
#include "ClientCore.h"
#include "PositionSystem.h"
#include "WeaponManagerSystem.h"

PlayerManager::PlayerManager() : EntityManager(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}


void	PlayerManager::addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::addEntity(owner, entity, rpc);
	ecs::PositionSystem::initScenePosition(*entity);
	ecs::WeaponManagerSystem::initWeapon(*entity);
	if (ClientCore::getInstance().getClientId() == owner)
		this->setCurrentPlayer(entity);
}

void	PlayerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);
}

void	PlayerManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	EntityManager::removeEntity(owner, rpc);
}


ecs::Entity*	PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}

void PlayerManager::setCurrentPlayer(ecs::Entity * localPlayer)
{
	m_currentPlayer = localPlayer;
}
