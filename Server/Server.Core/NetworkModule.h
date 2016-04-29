#pragma once

#include "StdInc.h"

#include <RakPeerInterface.h>
#include <RPC4Plugin.h>
#include <MessageIdentifiers.h>

#include "NetworkRPC.h"
#include "GeneralRPC.h"
#include "PlayerRPC.h"

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init(const std::string& address, short port, const std::string& password);
	void	pulse();

	void	callRPC(const std::string& rpc, RakNet::BitStream *bitStream, PacketPriority packetPriority, PacketReliability packetReliability, int playerId, bool broadcast);

	RakNet::RakPeerInterface*	getRakPeer();
	RakNet::RPC4*				getRPC();


private:
	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::RPC4*				m_rpc;
};
