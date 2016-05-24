#pragma once

#include <RPC3.h>
#include "Entity.h"
#include "WeaponManager.h"
#include "Life.h"

namespace ecs
{
	class WeaponSystem
	{
	public:
		WeaponSystem()	= delete;
		~WeaponSystem()	= delete;

		static void	shoot(Entity* entity, irr::core::line3df* ray, RakNet::RPC3* rpc);
	};
}
