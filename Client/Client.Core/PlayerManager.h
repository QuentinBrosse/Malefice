#pragma once

#include "EntityManager.h"
#include "Entity.h"

class PlayerManager : public EntityManager
{
public:
	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager()					= default;

	ecs::Entity*	getCurrentPlayer() const;
};
