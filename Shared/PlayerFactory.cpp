#include "PlayerFactory.h"
#include "Life.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "Position.h"
#include "SpellManager.h"
#include "Spell.h"
#include "SceneAnimatedMesh.h"
#include "NodePickable.h"

ecs::Entity* PlayerFactory::createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId, const int team, const int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::PLAYER);

	(*entity)[ecs::LIFE] = new ecs::Life(life, ecs::ComponentType::LIFE);
	(*entity)[ecs::TEAM] = new ecs::Team(team);
	(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true));
	(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	(*entity)[ecs::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_SHOOTABLE, true);

	return entity;
}

ecs::Entity* PlayerFactory::createPlayer(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId, const int team, const int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::PLAYER);

	(*entity)[ecs::LIFE] = new ecs::Life(life, ecs::ComponentType::LIFE);
	(*entity)[ecs::TEAM] = new ecs::Team(team);
	(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(ecs::Weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true));
	(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(device, newNameTexture, newNameMesh, vectorPosition, vectorRotation, networkId, 2, 1000);

	(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(vectorPosition, vectorRotation, networkId, 2, 1000);

	(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
