#include "EntityManager.h"

EntityManager::~EntityManager()
{

}

void EntityManager::addEntity(ecs::Entity *newPlayer)
{
	// A voir si il faut tester avant de l'ajouter
	m_entities[newPlayer->getNetworkID()] = newPlayer;
}

void EntityManager::removeEntity(ecs::NetworkID netID)
{
	m_entities.erase(netID);
}

bool	EntityManager::hasEntity(ecs::NetworkID netID)
{
	return m_entities.find(netID) != m_entities.end();
}

ecs::Entity* EntityManager::findEntity(ecs::NetworkID netID)
{
	return m_entities[netID];
}

