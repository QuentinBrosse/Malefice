
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

bool	NetworkModule::Init(std::string address, std::string port)
{
}