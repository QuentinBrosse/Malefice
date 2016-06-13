#pragma once

// Server Version

#include <RPC3.h>
#include "Entity.h"

namespace ecs
{

	class SpellManagerSystem
	{
	public:
		SpellManagerSystem() = delete;
		~SpellManagerSystem() = delete;

		static void	changeToNext(Entity* predator, RakNet::RPC3* rpc);
		static void	changeToPrec(Entity* predator, RakNet::RPC3* rpc);
	};

}