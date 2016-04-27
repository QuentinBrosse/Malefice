#pragma once

#include "../../Shared/StdInc.h"

#include <RakPeerInterface.h>
#include <RPC4Plugin.h>
#include <MessageIdentifiers.h>

class NetworkModule
{
private:
	RakNet::RakPeerInterface	*m_pRakPeer;
	RakNet::RPC4				*m_pRPC;

public:
	NetworkModule();
	~NetworkModule();

	bool						Init(std::string, std::string, std::string);
	void						Pulse();

	void						CallRPC(std::string, RakNet::BitStream *, PacketPriority, PacketReliability, int, bool);

	RakNet::RakPeerInterface	*GetRakPeer(void) { return m_pRakPeer; }
	RakNet::RPC4				*GetRPC(void) { return m_pRPC; }
};