#pragma once

#include "Movement.h"
#include "Entity.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT MovementSystem
	{
	public:
		MovementSystem() = delete;
		~MovementSystem() = delete;

		static void	move(Entity& entity);
	};
}
