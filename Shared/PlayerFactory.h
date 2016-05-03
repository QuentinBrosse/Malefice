#pragma once

#include "ObjectFactory.h"
#include "Entity.h"

class PlayerFactory
{
public:
	PlayerFactory()		= delete;
	~PlayerFactory()	= delete;

	static ecs::Entity *createPlayer(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const unsigned int networkId, const int team, int life);
	static ecs::Entity *createPredator(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const unsigned int networkId);
};
