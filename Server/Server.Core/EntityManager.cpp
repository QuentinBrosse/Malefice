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
	ecs::Position*	pos = dynamic_cast<ecs::Position*>(localEntity[ecs::AComponent::ComponentType::POSITION]);

	LOG_DEBUG(ECS) << "Updated pos for client " << owner << ": " << *pos;
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
