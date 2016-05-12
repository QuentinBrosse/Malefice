#include "ObjectFactory.h"


ecs::Entity* ObjectFactory::createObject(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::PlayerId owner)
{
	ecs::Entity* entity = new ecs::Entity(owner);

	(*entity)[ecs::POSITION] = new ecs::Position(vectorPosition, vectorRotation);

	return entity;
}
