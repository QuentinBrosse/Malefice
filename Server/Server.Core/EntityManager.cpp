#include "EntityManager.h"
#include "Logger.h"
#include "Position.h"

EntityManager::~EntityManager()
{
	for (auto entity : m_entities)
		delete entity.second;
}

void	EntityManager::updateEntity(ecs::ClientId owner, ecs::Entity *entity, RakNet::RPC3* rpc)
{
	ecs::Entity&	localEntity = *m_entities[owner];

	localEntity = *entity;
}

bool	EntityManager::hasEntity(ecs::ClientId owner)	const
{
	return m_entities.find(owner) != m_entities.end();
}

ecs::Entity*	EntityManager::findEntity(ecs::ClientId owner)	const
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
		return it->second;
	else
		LOG_ERROR(ECS) << "Could not find entity with owner = " << owner << ".";
}

int	EntityManager::getPoolSize() const
{
	return m_entities.size();
}