
#include "NetworkModule.h"

NetworkModule::NetworkModule()
{
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	m_pRPC = RakNet::RPC4::GetInstance();

	m_pRakPeer->AttachPlugin(m_pRPC);
}

NetworkModule::~NetworkModule()
{
	m_pRakPeer->Shutdown(500);

	m_pRakPeer->DetachPlugin(m_pRPC);

	RakNet::RPC4::DestroyInstance(m_pRPC);

	RakNet::RakPeerInterface::DestroyInstance(m_pRakPeer);
}

bool	NetworkModule::Init(std::string address, std::string port)
{

}