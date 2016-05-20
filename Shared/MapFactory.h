#pragma once

#include <irrlicht.h>
#include "Entity.h"
#include "Position.h"

class MALEFICE_DLL_EXPORT MapFactory
{
public:
	MapFactory() = delete;
	~MapFactory() = delete;

	static ecs::Entity*	createMap(irr::IrrlichtDevice* device, const ecs::Position position, const ecs::ClientId owner, const std::string& nameMesh, const std::string& namePK3 = "");
};