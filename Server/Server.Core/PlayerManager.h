#pragma once

#include <RPC3.h>
#include "EntityManager.h"
#include "AComponent.h"
#include "NetworkObject.h"

class PlayerManager : public EntityManager, public NetworkObject
{
public:
	PlayerManager();
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	virtual void	createEntity(ecs::ClientId owner);
	virtual void	updateEntities();
	virtual void	deleteEntity(ecs::ClientId owner);

	void	setPlayerNickname(RakNet::RakString nickname, RakNet::RPC3* rpc);
};
