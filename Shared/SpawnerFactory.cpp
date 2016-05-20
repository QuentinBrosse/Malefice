#include "SpawnerFactory.h"
#include "Weapon.h"
#include "Position.h"
#include "Life.h"
#include "Spell.h"

ecs::Entity* SpawnerFactory::createWeaponSpawner(const ecs::Position position, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(position, networkId, ecs::Entity::EntityType::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::WEAPON] = new ecs::Weapon();
	
	return entity;
}

ecs::Entity* SpawnerFactory::createLifeSpawner(const ecs::Position position, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(position, networkId, ecs::Entity::EntityType::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(50, ecs::AComponent::ComponentType::LIFE);

	return entity;
}

ecs::Entity* SpawnerFactory::createSpellSpawner(const ecs::Position position, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(position, networkId, ecs::Entity::EntityType::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell();

	return entity;
}