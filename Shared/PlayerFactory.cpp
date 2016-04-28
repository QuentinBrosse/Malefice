#include "PlayerFactory.h"
#include "ObjectFactory.h"
#include "CollectionComponent.h"
#include "Life.h"
#include "PlayerID.h"

namespace factory
{
	ecs::Entity& player(ecs::Entity& entity, int player_id, int team)
	{
		object(entity);
		entity[ecs::LIFE] = new ecs::Life(100);
		entity[ecs::PLAYER_ID] = new ecs::PlayerID(player_id);
		return entity;
	}

	ecs::Entity& predator(ecs::Entity& entity)
	{
		object(entity);
		entity[ecs::LIFE] = new ecs::Life(1000);
		entity[ecs::PLAYER_ID] = new ecs::PlayerID(0);
		// TEAM NUMBER WHILE BE 0
		return entity;
	}
}