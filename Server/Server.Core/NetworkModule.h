#pragma once

#include <string>
#include <RakPeerInterface.h>
#include <RPC3.h>
#include <RakNetTypes.h>
#include "NetworkObject.h"
#include "Logger.h"

class NetworkModule
{
public:
	NetworkModule();
	~NetworkModule();

	bool	init(const std::string& address, unsigned short port, const std::string& password);
	void	pulse();

	template<typename... Args>
	void	callRPC(const std::string& rpc, RakNet::NetworkID networkId, const RakNet::SystemAddress& to, bool broadcast, Args... args)
	{
		RakNet::RPC3::CallExplicitParameters	callExplicitParameters(networkId, to, broadcast, 0, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0);

		LOG_TRACE(NETWORK) << "Calling RPC \"" << rpc << "\".";
		m_rpc.CallExplicit(rpc.c_str(), &callExplicitParameters, args..., m_rpc);
	}


private:
	static const RakNet::TimeMS	TIMEOUT_MS;
	static const RakNet::TimeMS	SHUTDOWN_TIMEOUT_MS;

	void	registerRPCs();
	void	unregisterRPCs();

	void	acceptClient(RakNet::Packet* packet);


	RakNet::RakPeerInterface*	m_rakPeer;
	RakNet::RPC3				m_rpc;
};
