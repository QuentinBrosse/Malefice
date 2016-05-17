// Client Version

#include "MovementSystem.h"

namespace ecs
{

	void			MovementSystem::move(Entity& entity)
	{
		Movement*	movement;
		Position*	position;

		if ((movement = dynamic_cast<Movement*>(entity[ecs::AComponent::ComponentType::MOVEMENT])) != nullptr && (position = dynamic_cast<Position*>(entity[ecs::AComponent::ComponentType::POSITION])) != nullptr)
		{
			movement->move(*position);
			//TODO: send msg to server
		}
	}

}