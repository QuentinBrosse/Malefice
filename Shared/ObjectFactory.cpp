#include "ObjectFactory.h"

namespace factory
{
	ecs::Entity ObjectFactory::createObject(float x, float y, float z)
	{
		ecs::Entity	entity;

		entity[ecs::POSITION] = new ecs::Position(x, y, z);
		return entity;
	}
}
