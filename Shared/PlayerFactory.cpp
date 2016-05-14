#include "PlayerFactory.h"
#include "Life.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "Position.h"
#include "SpellManager.h"
#include "GameEventReceiver.h"
#include "Spell.h"
#include "SceneAnimatedMesh.h"
#include "NodePickable.h"

ecs::Entity* PlayerFactory::createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId playerID, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const int team, const int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, playerID, ecs::Entity::PLAYER);

	(*entity)[ecs::LIFE] = new ecs::Life(life, ecs::ComponentType::LIFE);
	(*entity)[ecs::TEAM] = new ecs::Team(team);
	ecs::Weapon* weapon = new ecs::Weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true);
	ecs::Weapon* weaponSniper = new ecs::Weapon(1, "sniper", 100, 50, 20, 50, 10, 5, ecs::Weapon::SNIPER_RIFLE, true);

	(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager();
	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::WEAPON_MANAGER])->createWeapon(device, "", "weapons/models/shotgun.obj", *weapon);
	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::WEAPON_MANAGER])->createWeapon(device, "", "weapons/models/sniper.obj", *weaponSniper);

	(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);

	(*entity)[ecs::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_SHOOTABLE, true);

	ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*entity)[ecs::SCENE]);
	scene->setAnimation(irr::scene::EMAT_ATTACK);

	(*entity)[ecs::GAME_EVENT_RECEIVER] = new ecs::GameEventReceiver();
	device->setEventReceiver(dynamic_cast<irr::IEventReceiver*>((*entity)[ecs::GAME_EVENT_RECEIVER]));



	return entity;
}

ecs::Entity*	PlayerFactory::createPlayer(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const int team, const int life)
{
	ecs::Entity*	entity = ObjectFactory::createObject(vectorPosition, vectorRotation, id, ecs::Entity::PLAYER);

	(*entity)[ecs::LIFE] = new ecs::Life(life, ecs::ComponentType::LIFE);
	(*entity)[ecs::TEAM] = new ecs::Team(team);
	ecs::Weapon weapon(1, "gun", 100, 50, 20, 50, 10, 5, ecs::Weapon::REVOLVER, true);
	(*entity)[ecs::WEAPON_MANAGER] = new ecs::WeaponManager(weapon);
	(*entity)[ecs::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	return entity;
}

ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const ecs::ClientId playerID, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(device, newNameTexture, newNameMesh, playerID, vectorPosition, vectorRotation, 2, 1000);

	(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(id, vectorPosition, vectorRotation, 2, 1000);

	(*entity)[ecs::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
