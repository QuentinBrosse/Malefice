#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <PacketPriority.h>
#include <RPC3.h>

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init();
	bool	connect(const std::string& address, unsigned short port, const std::string& password);
	void	disconnect();
	void	pulse();


	RakNet::ConnectionState	getConnectionState()	const;


	template<typename... Args>
	void	callRPC(const std::string& rpc, RakNet::NetworkID networkId, Args... args)
	{
		RakNet::RPC3::CallExplicitParameters	callExplicitParameters(networkId, m_serverAddress, false, 0, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0);

		LOG_TRACE(NETWORK) << "Calling RPC \"" << rpc << "\".";
		m_rpc.CallExplicit(rpc.c_str(), &callExplicitParameters, args..., m_rpc);
	}


private:
	static const RakNet::TimeMS	TIMEOUT_MS;
	static const RakNet::TimeMS	SHUTDOWN_TIMEOUT_MS;

	void	registerRPCs();
	void	unregisterRPCs();


	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::SystemAddress		m_serverAddress;
	RakNet::ConnectionState		m_connectionState;
	RakNet::RPC3				m_rpc;
};
