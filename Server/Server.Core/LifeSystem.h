#pragma once

#include "Entity.h"

namespace ecs
{
	class LifeSystem
	{
	public:
		LifeSystem()	= delete;
		~LifeSystem()	= delete;

		static void	die(ecs::Entity* dead);
	};
}
