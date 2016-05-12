#pragma once

// Server Version

#include "Entity.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager();

	virtual void			addEntity(ecs::Entity* newEntity);
	virtual void			removeEntity(ecs::PlayerId owner);

	virtual bool			hasEntity(ecs::PlayerId owner);

	virtual ecs::Entity*	findEntity(ecs::PlayerId owner);

protected:
	std::map<ecs::PlayerId, ecs::Entity*>	m_entities;
};