#pragma once

#include "EntityManager.h"
#include "Entity.h"

class PlayerManager : public EntityManager
{
public:
	PlayerManager()						= default;
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	virtual void	createEntity(ecs::ClientId owner);
	virtual void	deleteEntity(ecs::ClientId owner);
};
