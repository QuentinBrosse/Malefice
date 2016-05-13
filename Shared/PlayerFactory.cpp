#include "PlayerFactory.h"
#include "Life.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "Position.h"
#include "SpellManager.h"
#include "Spell.h"

ecs::Entity*	PlayerFactory::createPlayer(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const int team, const int life)
{
	ecs::Entity*	entity = ObjectFactory::createObject(vectorPosition, vectorRotation, id, ecs::Entity::PLAYER);

	(*entity)[ecs::LIFE] = new ecs::Life(life);
	(*entity)[ecs::TEAM] = new ecs::Team(team);
	(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true));
	(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	return entity;
}



ecs::Entity* PlayerFactory::createPredator(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(id, vectorPosition, vectorRotation, 2, 1000);

	(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
