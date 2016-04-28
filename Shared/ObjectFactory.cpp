#include "ObjectFactory.h"

#include "CollectionComponent.h"
#include "Position.h"

namespace factory
{
	ecs::Entity& object(ecs::Entity & entity)
	{
		entity[ecs::POSITION] = new ecs::Position(0, 0, 0);
		return entity;
	}
}
