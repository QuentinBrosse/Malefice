#pragma once

#include <map>
#include "BitStream.h"
#include "WeaponsConfiguration.h"
#include "Entity.h"
#include "EntityManager.h"
#include "PlayerManager.h"
#include "WeaponManager.h"
#include "SpawnerFactory.h"
#include "AScene.h"
#include "Export.h"
#include "Singleton.h"
#include "MathUtility.h"
#include "GraphicUtil.h"
#include "PositionSystem.h"

class SpawnerManager : public EntityManager, public Singleton<SpawnerManager>
{
	friend class Singleton<SpawnerManager>;
protected:
	SpawnerManager();
	~SpawnerManager();

public:
	std::map<ecs::ClientId, ecs::Entity*> getSpawners() const;

public:
	virtual void	addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc);

public:
	void initSpawnersScene();
	void regenerate(ecs::ClientId owner);

public:
	ecs::Entity* seekSpawnerById(ecs::ClientId owner);

public:
	void lifeRegeneration(ecs::Entity* spawner);
	void armorRegeneration(ecs::Entity* spawner);
	void weaponRegeneration(ecs::Entity* spawner);

public:
	void pickObject(ecs::Entity* spawner, ecs::Entity* player);
	void collisionDetection(ecs::Entity& entity);
	void drawLine();

public:
	void dump() const;

public:
	void	setSpawnerVisibility(ecs::Entity* player, const bool isVisible, RakNet::RPC3* rpc);

private:
	std::map<ecs::ClientId, irr::core::line3df> m_spawnLine;
	float	m_inc;
};