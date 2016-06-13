// Server Version

#include "SpellManagerSystem.h"
#include "SpellManager.h"
#include "ServerCore.h"

namespace ecs
{

	void SpellManagerSystem::changeToNext(Entity* predator, RakNet::RPC3* rpc)
	{
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(predator->getOwner());

		*entity = *predator;
	}

	void SpellManagerSystem::changeToPrec(Entity* predator, RakNet::RPC3* rpc)
	{
		ecs::Entity*	entity = ServerCore::getInstance().getPlayerManager().findEntity(predator->getOwner());

		*entity = *predator;
	}

}