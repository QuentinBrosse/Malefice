// Server Version

#include "WeaponManagerSystem.h"
#include "WeaponManager.h"

namespace ecs
{

	void WeaponManagerSystem::changeToNext(Entity* playerClient, RakNet::RPC3* rpc)
	{
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(playerClient->getOwner());

		*entity = *playerClient;
	}

	void WeaponManagerSystem::changeToPrec(Entity* playerClient, RakNet::RPC3* rpc)
	{
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(playerClient->getOwner());

		*entity = *playerClient;
	}
}