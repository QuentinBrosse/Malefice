#include "EntityManager.h"
#include "Logger.h"
#include "Position.h"
#include "WeaponManager.h"
#include "SpellManager.h"

EntityManager::~EntityManager()
{
	for (auto entity : m_entities)
		delete entity.second;
}

void	EntityManager::updateEntity(ecs::ClientId owner, ecs::Entity *entity, RakNet::RPC3* rpc)
{
	ecs::Position*		posLocal;
	ecs::Position*		posClient;
	ecs::Entity&		localEntity = *m_entities[owner];

	if ((posLocal = dynamic_cast<ecs::Position*>(localEntity[ecs::AComponent::ComponentType::POSITION])) != nullptr && (posClient = dynamic_cast<ecs::Position*>((*entity)[ecs::AComponent::ComponentType::POSITION])) != nullptr)
		posLocal->affect(*posClient);
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

std::map<ecs::ClientId, ecs::Entity*> EntityManager::getEntities() const
{
	return m_entities;
}
