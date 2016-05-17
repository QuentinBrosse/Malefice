#include "PlayerManager.h"

PlayerManager::PlayerManager() : EntityManager(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}

ecs::Entity*	PlayerManager::getCurrentPlayer() const
{
	return (nullptr);
}