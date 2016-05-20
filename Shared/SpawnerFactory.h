#pragma once

#include "ObjectFactory.h"
#include "Entity.h"
#include "Export.h"
#include "WeaponsConfiguration.h"

class MALEFICE_DLL_EXPORT SpawnerFactory
{
public:
	SpawnerFactory() = delete;
	~SpawnerFactory() = delete;

	static ecs::Entity* createWeaponSpawner(const ecs::Position position, const ecs::ClientId owner, WeaponsConfiguration* weaponConfig);
	static ecs::Entity* createLifeSpawner(const ecs::Position position, const ecs::ClientId owner);
	static ecs::Entity* createSpellSpawner(const ecs::Position position, const ecs::ClientId owner);

};