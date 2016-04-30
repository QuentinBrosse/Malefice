#pragma once

#include "Movement.h"
#include "Entity.h"

namespace ecs
{

	class MovementSystem
	{
	public:
		MovementSystem() = delete;
		~MovementSystem() = delete;

	private:
		static void	move(Entity& entity);
	};

}