#pragma once

#include <RPC3.h>
#include "Entity.h"
#include "WeaponManager.h"
#include "RakNetUtility.h"
#include "Life.h"
#include "Export.h"
#include "Line3dWrapper.h"

namespace ecs
{
	class WeaponSystem
	{
	public:
		WeaponSystem()	= delete;
		~WeaponSystem()	= delete;

		static void	shoot(Entity* entity, Line3dWrapper* rayWrap, RakNet::RPC3* rpc);
		static void reload(Entity* entityClient, RakNet::RPC3* rpc);
	};
}
