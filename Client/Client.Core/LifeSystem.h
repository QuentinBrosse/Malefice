#pragma once

#include <RPC3.h>
#include "Entity.h"

class LifeSystem
{
public:
	LifeSystem()	= delete;
	~LifeSystem()	= delete;

	static void	die(RakNet::RPC3* rpc);
};
