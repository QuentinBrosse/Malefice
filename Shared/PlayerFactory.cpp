#include "PlayerFactory.h"
#include "Life.h"
#include "NetworkID.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "Position.h"
#include "SpellManager.h"
#include "Spell.h"

namespace factory
{
	ecs::Entity PlayerFactory::createPlayer(float x, float y, float z, unsigned int networkId, int team, int life)
	{
		ecs::Entity	entity = ObjectFactory::createObject(x, y, z);

		entity[ecs::LIFE] = new ecs::Life(life);
		entity[ecs::NETWORK_ID] = new ecs::NetworkID(networkId);
		entity[ecs::TEAM] = new ecs::Team(team);
		entity[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon(1, "gun", 10, 5, 20, 50, ecs::Weapon::REVOLVER, true)); // FIXME: ???
		entity[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(x, y, z));
		entity[ecs::SPELL] = new ecs::Spell();

		return entity;
	}

	ecs::Entity PlayerFactory::createPredator(float x, float y, float z, unsigned int networkId)
	{
		ecs::Entity entity = PlayerFactory::createPlayer(x, y, z, networkId, 2, 1000);

		entity[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(ecs::Spell::CONFUSION));

		return entity;
	}
}