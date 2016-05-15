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


	/// Parameters passed to Call are processed as follows:
	/// 1. If the parameter is not a pointer
	/// 2. - And you overloaded RakNet::BitStream& operator<<(RakNet::BitStream& out, MyClass& in) then that will be used to do the serialization
	/// 3. - Otherwise, it will use bitStream.Write(myClass); BitStream already defines specializations for NetworkIDObject, SystemAddress, other BitStreams
	/// 4. If the parameter is a pointer
	/// 5. - And the pointer can be converted to NetworkIDObject, then it will write bitStream.Write(myClass->GetNetworkID()); To make it also dereference the pointer, use RakNet::_RPC3::Deref(myClass)
	/// 6. - And the pointer can not be converted to NetworkID, but it is a pointer to RakNet::RPC3, then it is skipped
	/// 7. Otherwise, the pointer is dereferenced and written as in step 2 and 3.
	///
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
