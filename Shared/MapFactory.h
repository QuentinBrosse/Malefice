#pragma once

#include <irrlicht.h>

#include "NetworkID.h"
#include "Entity.h"

class MALEFICE_DLL_EXPORT MapFactory
{
public:
	MapFactory() = delete;
	~MapFactory() = delete;

	static ecs::Entity*	createMap(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::NetworkID netID, const std::string& nameMesh, const std::string& namePK3 = "");
};