#include "PlayerFactory.h"
#include "Life.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "PlayerInfos.h"
#include "Position.h"
#include "SpellManager.h"
#include "GameEventReceiver.h"
#include "Spell.h"
#include "SceneAnimatedMesh.h"
#include "NodePickable.h"
#include "WeaponCreator.h"
#include "Logger.h"

ecs::Entity* PlayerFactory::createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId playerID, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, ecs::Team::TeamType team, const int life)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, playerID, ecs::Entity::EntityType::PLAYER);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);

	WeaponCreator& weaponCreator = WeaponCreator::getInstance();

	ecs::Weapon weaponShotGun = weaponCreator.create(ecs::Weapon::WeaponType::SHOT_GUN);

	ecs::Weapon* weaponSniper = new ecs::Weapon();

	weaponSniper->init(2,
			"sniper",
			"sniper.obj",
			ecs::Weapon::WeaponType::SNIPER_RIFLE,
			10.0, 1, 10, 1, 1, 1, 1,
			ecs::Position(irr::core::vector3df(1.2f, -0.8f, 1.5f),
			irr::core::vector3df(0.f, 0.f, 0.f),
			irr::core::vector3df(20.0f, 20.0f, 15.f)),
			ecs::Position(irr::core::vector3df(),
			irr::core::vector3df(),
			irr::core::vector3df()),
			true, 100);

	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = new ecs::WeaponManager();

	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->createWeapon(device, weaponShotGun);
	dynamic_cast<ecs::WeaponManager*>((*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->createWeapon(device, *weaponSniper);

	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);

	(*entity)[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_SHOOTABLE, true, false, 0);

	ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*entity)[ecs::AComponent::ComponentType::SCENE]);
	scene->setAnimation(irr::scene::EMAT_ATTACK);

	(*entity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER] = new ecs::GameEventReceiver();
	device->setEventReceiver(dynamic_cast<irr::IEventReceiver*>((*entity)[ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER]));

	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();



	return entity;
}

ecs::Entity*	PlayerFactory::createPlayer(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, ecs::Team::TeamType team, const int life)
{
	ecs::Entity*	entity = ObjectFactory::createObject(vectorPosition, vectorRotation, id, ecs::Entity::EntityType::PLAYER);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);
	ecs::Weapon weapon;
	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = new ecs::WeaponManager(weapon);
	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(vectorPosition, vectorRotation));
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();
	return entity;
}

ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const ecs::ClientId playerID, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(device, newNameTexture, newNameMesh, playerID, vectorPosition, vectorRotation, ecs::Team::TeamType::Predator, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(ecs::ClientId id, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(id, vectorPosition, vectorRotation, ecs::Team::TeamType::Predator, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
