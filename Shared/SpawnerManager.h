#pragma once

#include <map>
#include "BitStream.h"
#include "WeaponsConfiguration.h"
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT SpawnerManager
{
public:
	SpawnerManager();
	~SpawnerManager();

public:
	std::map<ecs::ClientId, ecs::Entity*> getSpawners() const;

public:
	void add(ecs::Entity* newSpawner);
	void regenerate(ecs::ClientId owner, WeaponsConfiguration* weaponConfig);
	void remove(ecs::ClientId owner);

public:
	ecs::Entity* seekSpawnerById(ecs::ClientId owner);

public:
	void SpawnerManager::lifeRegeneration(ecs::Entity* spawner);
	void SpawnerManager::armorRegeneration(ecs::Entity* spawner);
	void SpawnerManager::weaponRegeneration(ecs::Entity* spawner, WeaponsConfiguration* weaponConfig);
public:
	void dump() const;


private:
	std::map<ecs::ClientId, ecs::Entity*> m_spawners;
};