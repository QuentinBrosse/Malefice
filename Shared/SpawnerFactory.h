#pragma once

#include "ObjectFactory.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT SpawnerFactory
{
public:
	SpawnerFactory() = delete;
	~SpawnerFactory() = delete;

	static ecs::Entity* createWeaponSpawner(const ecs::Position position, const unsigned int networkId);
	static ecs::Entity* createLifeSpawner(const ecs::Position position, const unsigned int networkId);
	static ecs::Entity* createSpellSpawner(const ecs::Position position, const unsigned int networkId);

};