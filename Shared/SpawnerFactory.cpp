#include "SpawnerFactory.h"
#include "WeaponCreator.h"
#include "Position.h"
#include "Life.h"
#include "Armor.h"

ecs::Entity* SpawnerFactory::createWeaponSpawner(const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 10;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::WEAPON_SPAWNER);

	(*entity)[ecs::AComponent::ComponentType::WEAPON] = &WeaponCreator::getInstance().create((const ecs::Weapon::WeaponType)i);	
	return entity;
}

ecs::Entity* SpawnerFactory::createLifeSpawner(const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 10 + 1;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::LIFE_SPAWNER);

	if (i <= 5)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(20, ecs::AComponent::ComponentType::LIFE);
	else if (i >= 6 && i <= 8)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(40, ecs::AComponent::ComponentType::LIFE);
	else
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);

	return entity;
}

ecs::Entity* SpawnerFactory::createSpellSpawner(const ecs::Position position, const ecs::ClientId owner)
{
	int i = rand() % 5 + 1;
	ecs::Entity* entity = ObjectFactory::createObject(position, owner, ecs::Entity::EntityType::ARMOR_SPAWNER);

	if (i <= 4)
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(40);
	else
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(100);

	return entity;
}