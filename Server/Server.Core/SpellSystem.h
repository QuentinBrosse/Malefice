#pragma once

#include <RPC3.h>
#include "Entity.h"
#include "Line3dWrapper.h"

namespace ecs
{
	class SpellSystem
	{
	public:
		SpellSystem() = delete;
		~SpellSystem() = delete;

		static void	launchSpell(Entity* predator, Line3dWrapper* rayWrap, RakNet::RPC3* rpc);
	};
}
