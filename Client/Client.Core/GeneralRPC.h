#pragma once

#include <RPC3.h>
#include <BitStream.h>
#include "NetworkObject.h"

class GeneralRPC : public NetworkObject
{
public:
	GeneralRPC();
	~GeneralRPC();

	void playerChat(RakNet::BitStream* userData, RakNet::RPC3* remote);
};
