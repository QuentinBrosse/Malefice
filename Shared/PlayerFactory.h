#pragma once

#include "ObjectFactory.h"
#include "Entity.h"

namespace factory
{
	class PlayerFactory
	{
	public:
		PlayerFactory()		= delete;
		~PlayerFactory()	= delete;

		static ecs::Entity createPlayer(float x, float y, float z, unsigned int networkId, int team, int life);
		static ecs::Entity createPredator(float x, float y, float z, unsigned int networkId);
	};
}
