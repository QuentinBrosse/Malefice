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

	static ecs::Entity *createObject(const ecs::Position position, const ecs::ClientId owner, const ecs::Entity::EntityType entityType);
};
