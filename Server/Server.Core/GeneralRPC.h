#pragma once

#include <RPC3.h>
#include <BitStream.h>
#include "NetworkObject.h"

class GeneralRPC : public NetworkObject
{
public:
	GeneralRPC();
	virtual ~GeneralRPC();

	void	playerChat(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
};
