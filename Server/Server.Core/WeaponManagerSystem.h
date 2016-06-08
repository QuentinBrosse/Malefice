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

		static void	changeToNext(Entity* player, RakNet::RPC3* rpc);
		static void changeToPrec(Entity* player, RakNet::RPC3* rpc);
	};

}