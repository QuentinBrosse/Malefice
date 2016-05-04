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

ecs::Entity* PlayerFactory::createPlayer(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const unsigned int networkId, const int team, const int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(xPosition, yPosition, zPosition, xTarget, yTarget, zTarget, networkId);

		(*entity)[ecs::LIFE] = new ecs::Life(life);
		(*entity)[ecs::TEAM] = new ecs::Team(team);
		(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true));
		(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(xPosition, yPosition, zPosition, xTarget, yTarget, zTarget));
		(*entity)[ecs::SPELL] = new ecs::Spell(ecs::Spell::SpellType::NOTHING, 60);

		return entity;
	}



ecs::Entity* PlayerFactory::createPredator(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const unsigned int networkId)
	{
	ecs::Entity* entity = PlayerFactory::createPlayer(xPosition, yPosition, zPosition, xTarget, yTarget, zTarget, networkId, 2, 1000);

		(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(ecs::Spell::CONFUSION, 5));

		return entity;
	}
