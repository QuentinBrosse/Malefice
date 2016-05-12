#pragma once

// Client Version

#include "Entity.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager();

	void			addEntity(ecs::Entity* newEntity);
	void			removeEntity(ecs::NetworkID netID);

	bool			hasEntity(ecs::NetworkID netID);

	ecs::Entity*	findEntity(ecs::NetworkID netID);

protected:
	std::map<ecs::NetworkID, ecs::Entity*>	m_entities;
};