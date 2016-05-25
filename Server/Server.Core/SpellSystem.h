#pragma once

#include <RPC3.h>
#include "Entity.h"

namespace ecs
{
	class SpellSystem
	{
	public:
		SpellSystem() = delete;
		~SpellSystem() = delete;

		static void	launchSpell(Entity& predator, RakNet::RPC3* rpc);
	};
}
