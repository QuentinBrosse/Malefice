#include "ObjectFactory.h"
#include "Position.h"

ecs::Entity* ObjectFactory::createObject(const float xPosition,  const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget)
{
	ecs::Entity* entity = new ecs::Entity();

	(*entity)[ecs::POSITION] = new ecs::Position(xPosition, yPosition, zPosition, xTarget, yTarget, zTarget);

	return entity;
}