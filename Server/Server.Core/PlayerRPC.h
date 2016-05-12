#pragma once

#include <RPC3.h>
#include <BitStream.h>
#include "NetworkObject.h"

class PlayerRPC : public NetworkObject
{
public:
	PlayerRPC();
	~PlayerRPC();

	void	playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
	void	playerSync(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
};
