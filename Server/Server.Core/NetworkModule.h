#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RPC3.h>
#include <NetworkIDManager.h>
#include "GeneralRPC.h"
#include "PlayerRPC.h"

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init(const std::string& address, unsigned short port, const std::string& password);
	void	pulse();

	void	callRPC(const std::string& rpc, RakNet::NetworkIDObject* object, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, RakNet::SystemAddress to, bool broadcast);


	RakNet::RPC3*				getRPC();
	RakNet::NetworkIDManager*	getNetworkIDManager();


private:
	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::RPC3*				m_rpc;
	RakNet::NetworkIDManager	m_networkIDManager;
	GeneralRPC*					m_generalRPC;
	PlayerRPC*					m_playerRPC;
};
