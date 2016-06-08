#pragma once

// Client Version

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
		WeaponSystem() = delete;
		~WeaponSystem() = delete;
		static void						shoot(Entity& entity);
		static void						triggerShootActions(Entity* entity, int status, RakNet::RPC3* rpc);
	};
}
