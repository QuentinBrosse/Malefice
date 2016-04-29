#include "PlayerFactory.h"

namespace factory
{
	ecs::Entity PlayerFactory::createPlayer(float x, float y, float z, networkID network_id, int team, int life)
	{
		ecs::Entity	entity = ObjectFactory::createObject(x, y, z);

		entity[ecs::LIFE] = new ecs::Life(life);
		entity[ecs::NETWORK_ID] = new ecs::NetworkID(network_id);
		entity[ecs::TEAM] = new ecs::Team(team);
		entity[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon("gun", 10, 5, 20, 50, ecs::Weapon::REVOLVER, true));
		entity[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(x, y, z));
	
		return entity;
	}

	ecs::Entity PlayerFactory::createPredator(float x, float y, float z, networkID networkId)
	{
		ecs::Entity entity = PlayerFactory::createPlayer(x, y, z, networkId, 2, 1000);

		entity[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(ecs::Spell::CONFUSION));
		return entity;
	}
}