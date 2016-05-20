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
	void regenerate(ecs::ClientId owner);
	void remove(ecs::ClientId owner);

public:
	ecs::Entity* seekSpawnerById(ecs::ClientId owner);

public:
	void lifeRegeneration(ecs::Entity* spawner);
	void armorRegeneration(ecs::Entity* spawner);
	void weaponRegeneration(ecs::Entity* spawner);

public:
	//void pickObject(ecs::ClientId owner);
	//Fonction qui renvoie s'il y a collisions (soit avec la ligne soit avec le perso)

public:
	void dump() const;


private:
	std::map<ecs::ClientId, ecs::Entity*> m_spawners;
};