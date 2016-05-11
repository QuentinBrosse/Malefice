#pragma once

#include <NetworkIDObject.h>
#include <RPC3.h>
#include <BitStream.h>

class PlayerRPC : public RakNet::NetworkIDObject
{
public:
	PlayerRPC();
	~PlayerRPC();

	void	playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
	void	playerSync(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
};
