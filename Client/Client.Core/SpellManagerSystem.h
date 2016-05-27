#pragma once

// Client Version

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
		static void changeManager(Entity& predator);
		static void initFPSScene(Entity& predator);
		static void initExternalScene(Entity & predator);
	};

}