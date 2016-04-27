
#include "NetworkModule.h"

NetworkModule::NetworkModule()
{
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	m_pRPC = RakNet::RPC4::GetInstance();

	// Todo : Register RPCs

	m_pRakPeer->AttachPlugin(m_pRPC);
}

NetworkModule::~NetworkModule()
{
	m_pRakPeer->Shutdown(500);

	// Todo : Unregister RPCs

	m_pRakPeer->DetachPlugin(m_pRPC);

	RakNet::RPC4::DestroyInstance(m_pRPC);

	RakNet::RakPeerInterface::DestroyInstance(m_pRakPeer);
}

bool	NetworkModule::Init(std::string address, std::string port, std::string password)
{
	RakNet::SocketDescriptor descriptor(std::stoi(port), port.c_str());

	if (m_pRakPeer->Startup(MAX_PLAYERS, &descriptor, 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		m_pRakPeer->SetMaximumIncomingConnections(MAX_PLAYERS);

		m_pRakPeer->SetTimeoutTime(10000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);

		if (password.length() > 0)
		{
			m_pRakPeer->SetIncomingPassword(password.c_str(), password.length());
		}
	}
	else
		return (false);

	return (true);
}