#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RPC4Plugin.h>

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

	void	connectionAccepted(RakNet::Packet * packet);

	void	callRPC(const std::string& rpc, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, bool broadcast);

	RakNet::RakPeerInterface*	getRakPeer();
	RakNet::RPC4*				getRPC();
	bool						isConnected()	const;

	void						setNetState(eNetworkState netState);
	eNetworkState				getNetState() const;

private:
	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::RPC4*				m_rpc;
	bool						m_connected;
	eNetworkState				m_netState;
};