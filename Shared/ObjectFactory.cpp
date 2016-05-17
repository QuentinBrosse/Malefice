#include "ObjectFactory.h"

ecs::Entity* ObjectFactory::createObject(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const ecs::ClientId owner, const ecs::Entity::EntityType entityType)
{
	ecs::Entity*	entity = new ecs::Entity(owner, entityType);

	(*entity)[ecs::AComponent::ComponentType::POSITION] = new ecs::Position(vectorPosition, vectorRotation);
	return entity;
}
