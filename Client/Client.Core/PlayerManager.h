#pragma once

#include "EntityManager.h"
#include "Entity.h"

// TODO: do we really need a PlayerManager or is an EntityManager enough?
class PlayerManager : public EntityManager
{
public:
	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager()					= default;

	ecs::Entity*	getCurrentPlayer() const;
};
