#pragma once

#include <RPC3.h>
#include "Entity.h"

namespace ecs
{
	class LifeSystem
	{
	public:
		LifeSystem()	= delete;
		~LifeSystem()	= delete;

		static void	die(ecs::Entity* dead);
		static void restore(ecs::Entity* entity, const int hp, RakNet::RPC3* rpc);
		void restoreArmor(ecs::Entity * entity, const int hp, RakNet::RPC3 * rpc);
	};
}
