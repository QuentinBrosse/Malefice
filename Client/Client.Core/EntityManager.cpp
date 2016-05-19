#include "EntityManager.h"
#include "Logger.h"

EntityManager::EntityManager(NetworkRPC::ReservedNetworkIds networkId) : NetworkObject(networkId),
	m_entities()
{
}

EntityManager::~EntityManager()
{
	for (auto entity : m_entities)
		delete entity.second;
}

void	EntityManager::addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	m_entities[owner] = entity;
	LOG_TRACE(NETWORK) << "EntityManager::addEntity received owner = " << owner << ", entity = " << *entity;
}

void	EntityManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	ecs::Entity&	localEntity = *m_entities[owner];

	localEntity = (*entity);
}

void	EntityManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
		m_entities.erase(it);
	else
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
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
