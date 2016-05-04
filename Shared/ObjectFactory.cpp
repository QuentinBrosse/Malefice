#include "ObjectFactory.h"


ecs::Entity* ObjectFactory::createObject(const float xPosition,  const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const ecs::NetworkID netID)
{
	ecs::Entity* entity = new ecs::Entity(netID);

	(*entity)[ecs::POSITION] = new ecs::Position(xPosition, yPosition, zPosition, xTarget, yTarget, zTarget);

	return entity;
}