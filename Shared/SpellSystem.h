#pragma once

#include "Entity.h"
#include "SpellManager.h"

namespace ecs
{
	class SpellSystem
	{
	public:
		SpellSystem() = delete;
		~SpellSystem() = delete;

		static void	launchSpell(Entity& predator, Entity& target);
	};

}