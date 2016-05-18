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
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, playerID, ecs::Entity::EntityType::PLAYER);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);
	ecs::Weapon* weapon = new ecs::Weapon();
	ecs::Weapon* weaponSniper = new ecs::Weapon();

	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = new ecs::WeaponManager();
	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->createWeapon(device, "", "weapons/models/shotgun.obj", *weapon);
	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->createWeapon(device, "", "weapons/models/sniper.obj", *weaponSniper);

	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);

	(*entity)[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_SHOOTABLE, true, true, 0);

	ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*entity)[ecs::AComponent::ComponentType::SCENE]);
	scene->setAnimation(irr::scene::EMAT_ATTACK);

	(*entity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER] = new ecs::GameEventReceiver();
	device->setEventReceiver(dynamic_cast<irr::IEventReceiver*>((*entity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER]));



	return entity;
}

ecs::Entity*	PlayerFactory::createPlayer(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const int team, const int life)
{
	ecs::Entity*	entity = ObjectFactory::createObject(vectorPosition, vectorRotation, id, ecs::Entity::EntityType::PLAYER);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);
	ecs::Weapon weapon;
	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = new ecs::WeaponManager(weapon);
	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	return entity;
}

ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const ecs::ClientId playerID, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(device, newNameTexture, newNameMesh, playerID, vectorPosition, vectorRotation, 2, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(id, vectorPosition, vectorRotation, 2, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
