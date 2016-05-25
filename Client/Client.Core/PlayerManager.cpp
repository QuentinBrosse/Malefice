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
	/*	GraphicUtil::getInstance().getDevice()->setEventReceiver(dynamic_cast<irr::IEventReceiver*>((*localEntity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER]));
		irr::IEventReceiver* sex = dynamic_cast<irr::IEventReceiver*>((*localEntity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER]);
		(*localEntity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER] = new ecs::GameEventReceiver();
		irr::IEventReceiver* bite =  GraphicUtil::getInstance().getDevice()->getEventReceiver();
		bite = bite;*/
	}
}

void	PlayerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);

	for (auto& pair : m_entities)		
		ecs::PositionSystem::updateScenePosition(*pair.second);
}

void	PlayerManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		ecs::Entity&	entity = *it->second;

		ecs::AScene*	scene = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE]);
		scene->getNode()->remove();
		m_entities.erase(it);
		LOG_INFO(ECS) << "Removed player entity with owner ID = " << owner << ".";
	}
	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}


void PlayerManager::initPlayersScene()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		PlayerFactory::initScene(GraphicUtil::getInstance().getDevice(), "sydney.bmp", "sydney.md2", *it->second);
		ecs::PositionSystem::updateScenePosition(*it->second);
	}
}

void PlayerManager::initPlayersWeapons()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		if (ClientCore::getInstance().getClientId() == it->first)
			ecs::WeaponManagerSystem::initFPSWeapon(*it->second);
		else
			ecs::WeaponManagerSystem::initExternalWeapon(*it->second);
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

const std::map<ecs::ClientId, ecs::Entity*> &PlayerManager::getEntities() const
{
	return m_entities;
}