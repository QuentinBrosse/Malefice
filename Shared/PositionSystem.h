#pragma once

#include "Entity.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT PositionSystem
	{
	public:
		PositionSystem() = delete;
		~PositionSystem() = delete;

		static void	update(Entity& entity);
	};
}