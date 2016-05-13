#pragma once

#include <irrlicht.h>

#include "Entity.h"
#include "Export.h"
#include "Position.h"

class MALEFICE_DLL_EXPORT ObjectFactory
{
public:
	ObjectFactory() = delete;
	~ObjectFactory() = delete;

	static ecs::Entity *createObject(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::ClientId, const ecs::Entity::EntityType entityType);
};
