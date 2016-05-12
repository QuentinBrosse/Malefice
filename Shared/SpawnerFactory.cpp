#include "SpawnerFactory.h"
#include "Weapon.h"
#include "Position.h"
#include "Life.h"
#include "Spell.h"

ecs::Entity* SpawnerFactory::createWeaponSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::WEAPON] = new ecs::Weapon();
	
	return entity;
}

ecs::Entity* SpawnerFactory::createLifeSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::LIFE] = new ecs::Life(50);

	return entity;
}

ecs::Entity* SpawnerFactory::createSpellSpawner(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const unsigned int networkId)
{
	ecs::Entity* entity = ObjectFactory::createObject(vectorPosition, vectorRotation, networkId, ecs::Entity::SPAWN);

	(*entity)[ecs::SPELL] = new ecs::Spell();

	return entity;
}