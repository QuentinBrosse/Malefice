#include "SpawnerFactory.h"
#include "SceneMesh.h"
#include "WeaponCreator.h"
#include "Position.h"
#include "Life.h"
#include "Armor.h"
#include "NodePickable.h"


ecs::Entity* SpawnerFactory::createWeaponSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner)
{
	//TODO TTH : Randomiser la mesh weapon
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
	//TODO TTH : 3 mesh de coeur différent à faire
	int i = rand() % 10 + 1;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::LIFE_SPAWNER);
	(*entity)[ecs::AComponent::ComponentType::SCENE] = new ecs::SceneAnimatedMesh(device, nullptr, "", std::string(std::string("weapons/models/") + std::string("flamethrowerhandle.obj")).c_str(), nodePickable::IS_PICKABLE, true, false, 0);

	if (i <= 5)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(20, ecs::AComponent::ComponentType::LIFE);
	else if (i >= 6 && i <= 8)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(40, ecs::AComponent::ComponentType::LIFE);
	else
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);

	return entity;
}

ecs::Entity* SpawnerFactory::createSpellSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner)
{
	//TODO TTH : 3 mesh d'armures différents à faire
	int i = rand() % 5 + 1;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::ARMOR_SPAWNER);

	if (i <= 4)
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(40);
	else
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(100);

	return entity;
}

void SpawnerFactory::initScene(irr::IrrlichtDevice* device, const std::string& newNameMesh, ecs::Entity& entity)
{
	ecs::SceneAnimatedMesh* scene = new ecs::SceneAnimatedMesh(device, nullptr, "", newNameMesh, (nodePickable::NOT_PICKABLE), true, true, 0);
	scene->getNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	entity[ecs::AComponent::ComponentType::SCENE] = scene;
}

