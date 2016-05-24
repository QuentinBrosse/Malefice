#pragma once

#include <RPC3.h>
#include "Entity.h"
#include "WeaponManager.h"
#include "Life.h"
#include "Export.h"

namespace ecs
{
	class WeaponSystem
	{
	public:
		WeaponSystem()	= delete;
		~WeaponSystem()	= delete;

		static void	shoot(Entity* entity, RakNet::RPC3* rpc);
	};
}
