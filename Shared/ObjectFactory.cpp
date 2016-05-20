#include "ObjectFactory.h"

ecs::Entity* ObjectFactory::createObject(const ecs::Position position, const ecs::ClientId owner, const ecs::Entity::EntityType entityType)
{
	ecs::Entity*	entity = new ecs::Entity(owner, entityType);

	(*entity)[ecs::AComponent::ComponentType::POSITION] = new ecs::Position(position);
	return entity;
}
