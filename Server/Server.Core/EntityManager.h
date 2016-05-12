#pragma once

// Server Version

#include "Entity.h"

class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager();

	virtual void			addEntity(ecs::Entity* newEntity);
	virtual void			removeEntity(ecs::NetworkID netID);

	virtual bool			hasEntity(ecs::NetworkID netID);

	virtual ecs::Entity*	findEntity(ecs::NetworkID netID);

protected:
	std::map<ecs::NetworkID, ecs::Entity*>	m_entities;
};