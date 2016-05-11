#pragma once

#include <NetworkIDObject.h>
#include <RPC3.h>
#include <BitStream.h>

class GeneralRPC : public RakNet::NetworkIDObject
{
public:
	GeneralRPC();
	~GeneralRPC();

	void playerChat(RakNet::BitStream* userData, RakNet::RPC3* remote);
};
