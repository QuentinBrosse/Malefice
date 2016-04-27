#pragma once

#include "../../Shared/StdInc.h"

#include <RakPeerInterface.h>
#include <RPC4Plugin.h>

class NetworkModule
{
private:
	RakNet::RakPeerInterface	*m_pRakPeer;
	RakNet::RPC4				*m_pRPC;

public:
	NetworkModule();
	~NetworkModule();

	bool						Init(std::string, std::string);

	RakNet::RakPeerInterface	*GetRakPeer(void) { return m_pRakPeer; }
	RakNet::RPC4				*GetRPC(void) { return m_pRPC; }
};