#include "SpawnerFactory.h"
#include "Weapon.h"
#include "Position.h"
#include "Life.h"
#include "Spell.h"

ecs::Entity* SpawnerFactory::createWeaponSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::WEAPON] = new ecs::Weapon();
	
	return entity;
}

ecs::Entity* SpawnerFactory::createLifeSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(50, ecs::AComponent::ComponentType::LIFE);

	return entity;
}

ecs::Entity* SpawnerFactory::createSpellSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::AComponent::ComponentType::SPELL] = new ecs::Spell();

	return entity;
}