#include "ObjectFactory.h"
#include "Position.h"

ecs::Entity* ObjectFactory::createObject(float x, float y, float z)
{
	ecs::Entity* entity = new ecs::Entity();

	(*entity)[ecs::POSITION] = new ecs::Position(x, y, z, 0, 0, 0);

	return entity;
}