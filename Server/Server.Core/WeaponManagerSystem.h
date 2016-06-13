#pragma once

// Server Version

#include <RPC3.h>
#include "ServerCore.h"
#include "Entity.h"
#include "RakNetUtility.h"

namespace ecs
{
	class WeaponManagerSystem
	{
	public:
		WeaponManagerSystem() = delete;
		~WeaponManagerSystem() = delete;

		static void	changeWeapon(Entity* player, RakNet::RPC3* rpc);
	};

}