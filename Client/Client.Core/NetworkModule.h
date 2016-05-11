#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <PacketPriority.h>
#include <RPC3.h>
#include <NetworkIDManager.h>
#include "GeneralRPC.h"
#include "PlayerRPC.h"

enum eNetworkState
{
	NETSTATE_NONE = 0,
	NETSTATE_TIMEOUT,
	NETSTATE_DISCONNECTED,
	NETSTATE_CONNECTING,
	NETSTATE_CONNECTED
};

enum eDisconnectReason
{
	DISCONNECT_TIMEOUT = 0,
	DISCONNECT_QUIT,
	DISCONNECT_KICKED,
	DISCONNECT_BANNED
};

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init();
	bool	connect(const std::string& address, short port, const std::string& password);
	void	disconnect();
	void	pulse();

	void	callRPC(const std::string& rpc, RakNet::NetworkIDObject* networkObject, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability);


	RakNet::RPC3*				getRPC();
	RakNet::NetworkIDManager*	getNetworkIDManager();
	bool						isConnected()	const;
	

private:
	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::SystemAddress		m_serverAddress;
	RakNet::RPC3*				m_rpc;
	RakNet::NetworkIDManager	m_networkIDManager;
	GeneralRPC*					m_generalRPC;
	PlayerRPC*					m_playerRPC;
	bool						m_connected;
	eNetworkState				m_netState;
};
