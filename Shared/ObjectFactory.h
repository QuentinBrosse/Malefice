#pragma once

#include "Entity.h"

class ObjectFactory
{
public:
	ObjectFactory() = delete;
	~ObjectFactory() = delete;

	static ecs::Entity *createObject(float x, float y, float z);
};	