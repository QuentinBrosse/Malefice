#pragma once

#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT ObjectFactory
{
public:
	ObjectFactory() = delete;
	~ObjectFactory() = delete;

	static ecs::Entity *createObject(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget);
};
