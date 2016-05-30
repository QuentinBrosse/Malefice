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
#include "SceneBillboardText.h"
#include "NodePickable.h"
#include "WeaponCreator.h"
#include "Logger.h"
#include "SpellCreator.h"

/*
* Client 
*/
ecs::Entity* PlayerFactory::createPlayer(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, ecs::ClientId playerID, const ecs::Position position, ecs::Team::TeamType team)
{
	//Global
	ecs::Entity* entity = ObjectFactory::createObject(position, playerID, ecs::Entity::EntityType::PLAYER);

	//Life
	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(50);

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
	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell();

	//Scene
	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, (nodePickable::IS_PICKABLE | nodePickable::IS_SHOOTABLE), true, false, 0);
	scene->setAnimation(irr::scene::EMAT_ATTACK);
	(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;

	//Player Infos
	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();

	return entity;
}

void			PlayerFactory::initNicknameNode(ecs::Entity* entity, irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent)
{
	ecs::PlayerInfos* playerInfos = dynamic_cast<ecs::PlayerInfos*>((*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS]);
	ecs::Position pseudoPosition(irr::core::vector3df(0.F, 35.F, 0.F), irr::core::vector3df(0.F, 0.F, 0.F), irr::core::vector3df(5.F, 5.F, 0.F));
	irr::video::SColor pseudoColor(255, 255, 255, 255);

	ecs::SceneBillboardText* nicknameNode = new ecs::SceneBillboardText(device, pseudoColor, playerInfos->getNickname(), pseudoPosition);

	playerInfos->setNicknameNode(nicknameNode);
	playerInfos->getNicknameNode()->setParent(parent);
}


ecs::Entity* PlayerFactory::createPredator(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const ecs::ClientId playerID, const ecs::Position position)
{
	//Global
	ecs::Entity* entity = ObjectFactory::createObject(position, playerID, ecs::Entity::EntityType::PLAYER);

	//Life
	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);
	(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(50);

	//Team
	(*entity)[ecs::AComponent::ComponentType::TEAM] = new ecs::Team(ecs::Team::TeamType::Predator);

	// SpellManager	
	(*entity)[ecs::AComponent::ComponentType::SPELL_MANAGER] = new ecs::SpellManager(SpellCreator::getInstance().create(ecs::Spell::SpellType::BLIND), 20);

	//Movement
	(*entity)[ecs::AComponent::ComponentType::MOVEMENT] = new ecs::Movement(ecs::Position(position));

	//Scene
	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, (nodePickable::IS_PICKABLE | nodePickable::IS_SHOOTABLE), true, false, 0);
	scene->setAnimation(irr::scene::EMAT_ATTACK);
	(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;

	//Player Infos
	(*entity)[ecs::AComponent::ComponentType::PLAYER_INFOS] = new ecs::PlayerInfos();

	return entity;
}

void PlayerFactory::initScene(irr::IrrlichtDevice * device, const std::string & newNameTexture, const std::string & newNameMesh, ecs::Entity & entity)
{
	entity[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, newNameTexture, newNameMesh, (nodePickable::IS_PICKABLE | nodePickable::IS_SHOOTABLE), true, false, 0);

	ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>(entity[ecs::AComponent::ComponentType::SCENE]);
	scene->setAnimation(irr::scene::EMAT_ATTACK);
}


