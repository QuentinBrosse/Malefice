#include "ObjectFactory.h"


ecs::Entity* ObjectFactory::createObject(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::NetworkID netID)
{
	ecs::Entity* entity = new ecs::Entity(netID);

	(*entity)[ecs::POSITION] = new ecs::Position(vectorPosition, vectorRotation);

	return entity;
}