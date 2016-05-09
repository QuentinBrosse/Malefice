#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RPC4Plugin.h>

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init(const std::string& address, unsigned short port, const std::string& password);
	void	pulse();

	void	callRPC(const std::string& rpc, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, int playerId, bool broadcast);


private:
	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::RPC4*				m_rpc;
};
