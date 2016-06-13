#pragma once

#include <RPC3.h>
#include "Entity.h"

class LifeSystem
{
public:
	LifeSystem()	= delete;
	~LifeSystem()	= delete;

	static void	die(RakNet::RakString str, RakNet::RPC3* rpc);
	static void kill(RakNet::RakString killed, RakNet::RPC3* rpc);
};
