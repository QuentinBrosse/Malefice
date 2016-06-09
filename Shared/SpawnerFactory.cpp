#include "SpawnerFactory.h"
#include "SceneMesh.h"
#include "WeaponCreator.h"
#include "Position.h"
#include "Life.h"
#include "Armor.h"
#include "NodePickable.h"


ecs::Entity* SpawnerFactory::createWeaponSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 10;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::WEAPON_SPAWNER);
	ecs::Weapon* pickweapon = new ecs::Weapon(WeaponCreator::getInstance().create((ecs::Weapon::WeaponType)i));

	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + pickweapon->getMeshName()).c_str(), nodePickable::NOT_PICKABLE, true, true, 0);
	scene->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;

	(*entity)[ecs::AComponent::ComponentType::WEAPON] = pickweapon;
	return entity;
}

ecs::Entity* SpawnerFactory::createLifeSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 10 + 1;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::LIFE_SPAWNER);
	ecs::SceneAnimatedMesh* scene;

	if (i <= 5)
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("heart.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(20, ecs::AComponent::ComponentType::LIFE);
	
	}
	else if (i >= 6 && i <= 8)
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("heart2.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(50, ecs::AComponent::ComponentType::LIFE);
	}
	else
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("heart3.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);
	}
	scene->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	return entity;
}

ecs::Entity* SpawnerFactory::createArmorSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 10;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::ARMOR_SPAWNER);
	ecs::SceneAnimatedMesh* scene;

	if (i <= 5)
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("armor.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(20);
	}
	else if (i >= 6 && i <= 8)
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("armor2.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(50);
	}
	else
	{
		scene = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("armor3.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);
		(*entity)[ecs::AComponent::ComponentType::SCENE] = scene;
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(100);
	}
	scene->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	return entity;
}

void SpawnerFactory::initScene(irr::IrrlichtDevice* device, const std::string& newNameMesh, ecs::Entity& entity)
{
	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, "", newNameMesh, nodePickable::NOT_PICKABLE, true, true, 0);
	scene->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	entity[ecs::AComponent::ComponentType::SCENE] = scene;
}

