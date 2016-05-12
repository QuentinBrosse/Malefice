#pragma once

#include <RPC3.h>
#include <BitStream.h>
#include "NetworkObject.h"

class PlayerRPC : public NetworkObject
{
public:
	PlayerRPC();
	~PlayerRPC();

	void	connectionAccepted();

	void	playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
	void	addPlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote);
	void	removePlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote);
};
