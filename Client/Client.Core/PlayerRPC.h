#pragma once

#include <NetworkIDObject.h>
#include <RPC3.h>
#include <BitStream.h>

class PlayerRPC : public RakNet::NetworkIDObject
{
public:
	PlayerRPC();
	~PlayerRPC();

	void	connectionAccepted();

	void	playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
	void	addPlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote);
	void	removePlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote);
};
