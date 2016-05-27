#pragma once

// Client Version

#include "Entity.h"
#include "SpellManager.h"
#include "Export.h"

namespace ecs
{
	class SpellSystem
	{
	public:
		SpellSystem() = delete;
		~SpellSystem() = delete;

		static void	launchSpell(Entity& predator);
		static void affect(Entity& entity);
	};

}
