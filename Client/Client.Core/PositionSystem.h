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
		static void	initWeapon(Entity& entity);
		static void	initScenePosition(Entity& entity);
	};
}