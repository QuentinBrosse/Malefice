#pragma once

#include <irrlicht.h>
#include "Entity.h"

class MALEFICE_DLL_EXPORT MapFactory
{
public:
	MapFactory() = delete;
	~MapFactory() = delete;

	static ecs::Entity*	createMap(irr::IrrlichtDevice* device, const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::ClientId owner, const std::string& nameMesh, const std::string& namePK3 = "");
};