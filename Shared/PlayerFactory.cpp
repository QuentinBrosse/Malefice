#include "PlayerFactory.h"
#include "Armor.h"
#include "Team.h"
#include "WeaponManager.h"
#include "Weapon.h"
#include "Movement.h"
#include "PlayerInfos.h"
#include "Position.h"
#include "SpellManager.h"
#include "Spell.h"
#include "SceneAnimatedMesh.h"
#include "NodePickable.h"
#include "WeaponCreator.h"
#include "Logger.h"

/*
* Client 
*/
ecs::Entity* PlayerFactory::createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId playerID, const ecs::Position position, ecs::Team::TeamType team, const int life)
{
	//Global
	ecs::Entity* entity = ObjectFactory::createObject(position, playerID, ecs::Entity::EntityType::PLAYER);

	//Life
	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(life / 2);

	//Team
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);

	//Weapon
	WeaponCreator& weaponCreator = WeaponCreator::getInstance();
	ecs::WeaponManager* weaponManager = new ecs::WeaponManager();
	weaponManager->createWeapon(device, weaponCreator.create(ecs::Weapon::WeaponType::SHOT_GUN));
	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = weaponManager;

	//Movement
	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(position));

	//Spell
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);

	//Scene
	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_PICKABLE | nodePickable::IS_SHOOTABLE, true, false, 0);
	scene->setAnimation(irr::scene::EMAT_ATTACK);
	(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
	
	//Player Infos
	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();

	return entity;
}

/*
* Server
*/
ecs::Entity*	PlayerFactory::createPlayer(ecs::ClientId id, const ecs::Position position, ecs::Team::TeamType team, const int life)
{
	ecs::Entity*	entity = ObjectFactory::createObject(position, id, ecs::Entity::EntityType::PLAYER);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(life, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(life / 2);

	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(team);

	(*entity)[ecs::AComponent::ComponentType::WEAPON_MANAGER] = new ecs::WeaponManager();

	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(position);
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell(0, "default", ecs::Spell::SpellType::NOTHING, 60);
	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();
	return entity;
}

void PlayerFactory::initScene(irr::IrrlichtDevice * device, const std::string & newNameTexture, const std::string & newNameMesh, ecs::Entity & entity)
{
	WeaponCreator& weaponCreator = WeaponCreator::getInstance();

	ecs::Weapon weaponShotGun = weaponCreator.create(ecs::Weapon::WeaponType::SHOT_GUN);
	dynamic_cast<ecs::WeaponManager*>(entity[ecs::AComponent::ComponentType::WEAPON_MANAGER])->createWeapon(device, weaponShotGun);
	entity[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, nodePickable::IS_SHOOTABLE, true, false, 0);
	ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>(entity[ecs::AComponent::ComponentType::SCENE]);
	scene->setAnimation(irr::scene::EMAT_ATTACK);
}

ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const ecs::ClientId playerID, const ecs::Position position)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(device, newNameTexture, newNameMesh, playerID, position, ecs::Team::TeamType::Predator, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}

ecs::Entity* PlayerFactory::createPredator(ecs::ClientId id, const ecs::Position position)
{
	ecs::Entity* entity = PlayerFactory::createPlayer(id, position, ecs::Team::TeamType::Predator, 1000);

	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(ecs::Spell(1, "confusion", ecs::Spell::CONFUSION, 5));

	return entity;
}
