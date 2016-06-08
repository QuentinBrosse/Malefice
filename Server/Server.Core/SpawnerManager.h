#pragma once

#include <map>
#include <list>
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
#include "PhysicsUtil.h"
#include "PositionSystem.h"

class ServerCore;

class SpawnerManager : public EntityManager, public NetworkObject
{
public:
	SpawnerManager();
	SpawnerManager(const SpawnerManager&) = delete;
	~SpawnerManager()					  = default;

public:
	std::map<ecs::ClientId, ecs::Entity*> getSpawners() const;
	virtual void	addEntity(ecs::ClientId owner, ecs::Entity* entity);
	
	virtual void	createEntity(ecs::ClientId owner);
	virtual void	deleteEntity(ecs::ClientId owner);
	virtual void	updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	updateEntities();

	void regenerate(ecs::ClientId owner);
	ecs::Entity* seekSpawnerById(ecs::ClientId owner);
	
	void lifeRegeneration(ecs::Entity* spawner);
	void armorRegeneration(ecs::Entity* spawner);
	void weaponRegeneration(ecs::Entity* spawner);
	void pickObject(ecs::Entity* spawner, ecs::Entity* player);
	
	void collisionDetection(PlayerManager& m_player);
	
	void drawLine();
	void dump() const;

	void setSpawnerVisibility(ecs::Entity* spawner, const bool isVisible, RakNet::RPC3* rpc);

	void checkTimer();

private:
	std::map<ecs::ClientId, irr::core::line3df>		m_spawnLine;
	std::map<ecs::ClientId, long long>				m_timer;
	std::list<ecs::Position>						m_spawnPositionsWeapon;
	std::list<ecs::Position>						m_spawnPositionsLife;
	std::list<ecs::Position>						m_spawnPositionsArmor;

	float	m_inc;
};