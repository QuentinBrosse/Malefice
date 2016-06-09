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

	static ecs::Entity* createWeaponSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner);
	static ecs::Entity* createLifeSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner);
	static ecs::Entity* createArmorSpawner(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner);
	static void			initScene(irr::IrrlichtDevice* device, const std::string& newNameMesh, ecs::Entity& entity);
};