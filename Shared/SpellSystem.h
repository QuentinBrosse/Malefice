#pragma once

#include "Entity.h"
#include "SpellManager.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SpellSystem
	{
	public:
		SpellSystem() = delete;
		~SpellSystem() = delete;

		static void	launchSpell(Entity& predator, Entity& target);
	};

}
