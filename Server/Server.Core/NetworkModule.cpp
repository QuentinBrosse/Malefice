
#include "NetworkModule.h"

NetworkModule::NetworkModule()
{
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	m_pRPC = RakNet::RPC4::GetInstance();

	PlayerRPC::Register(m_pRPC);

	m_pRakPeer->AttachPlugin(m_pRPC);
}

NetworkModule::~NetworkModule()
{
	m_pRakPeer->Shutdown(500);

	PlayerRPC::Unregister(m_pRPC);

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

void	NetworkModule::Pulse()
{
	RakNet::Packet *pPacket = NULL;

	while (pPacket = m_pRakPeer->Receive())
	{
		switch (pPacket->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
			{
				std::cout << "[network] : Incoming connection from " << pPacket->systemAddress.ToString(true, ':') << std::endl;
				break;
			}
			
			case ID_DISCONNECTION_NOTIFICATION:
			{
				std::cout << "[network] : PlayerId " << pPacket->systemAddress.systemIndex << " disconnected" << std::endl;
				break;
			}

			case ID_CONNECTION_LOST:
			{
				std::cout << "[network] : PlayerId" << pPacket->systemAddress.systemIndex << " lost" << std::endl;
				break;
			}
		}
		
		m_pRakPeer->DeallocatePacket(pPacket);
	}
}

void	NetworkModule::CallRPC(std::string RPC, RakNet::BitStream *pBitstream, PacketPriority priority, PacketReliability reliatbility, int playerId, bool broadcast)
{
	if (m_pRPC)
		m_pRPC->Call(RPC.c_str(), pBitstream, priority, reliatbility, 0, (playerId != INVALID_PLAYER_ID ? m_pRakPeer->GetSystemAddressFromIndex(playerId) : RakNet::UNASSIGNED_SYSTEM_ADDRESS), broadcast);
}