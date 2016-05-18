#pragma once

#include <RPC3.h>
#include "NetworkObject.h"
#include "NetworkRPC.h"
#include "Entity.h"

class EntityManager : public NetworkObject
{
public:
	EntityManager(NetworkRPC::ReservedNetworkIds networkId);
	~EntityManager();

	virtual void	addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc);
	virtual void	removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc);

	bool			hasEntity(ecs::ClientId owner)	const;
	ecs::Entity*	findEntity(ecs::ClientId owner)	const;


protected:
	std::map<ecs::ClientId, ecs::Entity*>	m_entities;
};
