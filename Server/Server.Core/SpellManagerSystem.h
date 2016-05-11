#pragma once

// Server Version

#include "Entity.h"

namespace ecs
{

	class SpellManagerSystem
	{
	public:
		SpellManagerSystem() = delete;
		~SpellManagerSystem() = delete;

		static void	changeToNext(Entity& predator);
		static void	changeToPrec(Entity& predator);
	};

}