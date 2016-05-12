#pragma once

// Client Version

#include "Entity.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager();

	void			addEntity(ecs::Entity* newEntity);
	void			removeEntity(ecs::PlayerId owner);

	bool			hasEntity(ecs::PlayerId owner);

	ecs::Entity*	findEntity(ecs::PlayerId owner);

protected:
	std::map<ecs::PlayerId, ecs::Entity*>	m_entities;
};
