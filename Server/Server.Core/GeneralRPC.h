#pragma once

#include <NetworkIDObject.h>
#include <RPC3.h>
#include <BitStream.h>

class GeneralRPC : public RakNet::NetworkIDObject
{
public:
	GeneralRPC();
	virtual ~GeneralRPC();

	void	playerChat(RakNet::BitStream* bitStream, RakNet::RPC3* remote);
};
