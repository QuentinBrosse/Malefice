#include "MovementSystem.h"

namespace ecs
{

	void			MovementSystem::move(Entity& entity)
	{
		Movement*	movement;
		Position*	position;

		entity.dump();
		if ((movement = dynamic_cast<Movement*>(entity[MOVEMENT])) != nullptr && (position = dynamic_cast<Position*>(entity[POSITION])) != nullptr)
		{
			movement->dump();
			movement->move(*position);
		}
		entity.dump();
	}

}