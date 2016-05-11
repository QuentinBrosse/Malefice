#pragma once

#include "ObjectFactory.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT SpawnerFactory
{
public:
	SpawnerFactory() = delete;
	~SpawnerFactory() = delete;

	static ecs::Entity* createWeaponSpawner(const irr::core::vector3df & vectorPosition, const irr::core::vector3df & vectorRotation, const unsigned int networkId);
	static ecs::Entity* createLifeSpawner(const irr::core::vector3df & vectorPosition, const irr::core::vector3df & vectorRotation, const unsigned int networkId);
	static ecs::Entity* createSpellSpawner(const irr::core::vector3df & vectorPosition, const irr::core::vector3df & vectorRotation, const unsigned int networkId);

};