#pragma once

// Client Version

#include "Movement.h"
#include "Entity.h"
#include "Export.h"

namespace ecs
{
	class MovementSystem
	{
	public:
		MovementSystem() = delete;
		~MovementSystem() = delete;

		static void	move(Entity& entity);
	};
}
