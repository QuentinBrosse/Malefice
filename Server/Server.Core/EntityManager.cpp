// Server Version

#include "EntityManager.h"

EntityManager::~EntityManager()
{

}

void EntityManager::addEntity(ecs::Entity *newPlayer)
{
	// A voir si il faut tester avant de l'ajouter
	m_entities[newPlayer->getOwner()] = newPlayer;
}

void EntityManager::removeEntity(ecs::PlayerId owner)
{
	m_entities.erase(owner);
}

bool	EntityManager::hasEntity(ecs::PlayerId owner)
{
	return m_entities.find(owner) != m_entities.end();
}

ecs::Entity* EntityManager::findEntity(ecs::PlayerId owner)
{
	return m_entities[owner];
}

