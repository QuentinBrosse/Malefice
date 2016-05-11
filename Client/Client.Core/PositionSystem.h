#pragma once

// Client Version

#include "Entity.h"

namespace ecs
{
	class PositionSystem
	{
	public:
		PositionSystem() = delete;
		~PositionSystem() = delete;

		static void	update(Entity& entity);
	};
}