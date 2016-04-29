#pragma once

#include "ObjectFactory.h"
#include "CollectionComponent.h"
#include "Life.h"
#include "NetworkID.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Movement.h"
#include "SpellManager.h"

namespace factory
{
	class PlayerFactory
	{
	public:
		PlayerFactory() = delete;
		~PlayerFactory() = delete;
		ecs::Entity createPlayer(float x, float y, float z, networkID network_id, int team, int life);
		ecs::Entity createPredator(float x, float y, float z, networkID network_id);
	};
}