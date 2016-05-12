#include <MessageIdentifiers.h>
#include "NetworkModule.h"
#include "RakNetUtility.h"
#include "NetworkManager.h"
#include "Logger.h"

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_serverAddress(), m_rpc(new RakNet::RPC3()), m_generalRPC(nullptr), m_playerRPC(nullptr), m_connected(false), m_netState(NETSTATE_NONE)
{
	m_rpc->SetNetworkIDManager(&NetworkManager::getInstance().getNetworkIdManager());
	m_rakPeer->AttachPlugin(m_rpc);
}

NetworkModule::~NetworkModule()
{
	delete m_generalRPC;
	delete m_playerRPC;
	m_rakPeer->DetachPlugin(m_rpc);
	m_rakPeer->Shutdown(500);
	delete m_rpc;
	RakNet::RakPeerInterface::DestroyInstance(m_rakPeer);
}


bool	NetworkModule::init()
{
	if (m_rakPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool	NetworkModule::connect(const std::string& address, short port, const std::string& password)
{
	if (m_connected)
		return true;
	m_generalRPC = new GeneralRPC();
	m_playerRPC = new PlayerRPC();
	if (m_rakPeer->Connect(address.c_str(), port, password.c_str(), password.length()) == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
	{
		m_netState = NETSTATE_CONNECTING;
		m_connected = true;
		return true;
	}
	else
	{
		m_connected = false;
		return false;
	}
}

void	NetworkModule::disconnect()
{
	if (!m_connected)
		return;
	m_rakPeer->CloseConnection(RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	m_connected = false;
	m_netState = NETSTATE_DISCONNECTED;
}

void	NetworkModule::pulse()
{
	RakNet::Packet*	packet = nullptr;

	if (m_netState == NETSTATE_DISCONNECTED)
		return;
	while (packet = m_rakPeer->Receive())
	{
		if (packet == nullptr)
			continue;
		switch (packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			m_netState = NETSTATE_CONNECTED;
			m_serverAddress = packet->systemAddress;
			m_playerRPC->connectionAccepted();
			break;
		case ID_RPC_REMOTE_ERROR:
			RakNetUtility::logRPCRemoteError(static_cast<RakNet::RPCErrorCodes>(packet->data[1]), std::string(reinterpret_cast<char*>(packet->data) + 2));
			break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}


void	NetworkModule::callRPC(const std::string& rpc, RakNet::NetworkIDObject* networkObject, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability)
{
	RakNet::RPC3::CallExplicitParameters	callExplicitParameters(networkObject->GetNetworkID(), m_serverAddress, false, 0, packetPriority, packetReliability, 0);

	if (m_rpc != nullptr)
		m_rpc->CallExplicit(rpc.c_str(), &callExplicitParameters, bitStream, m_rpc);
}



RakNet::RPC3*	NetworkModule::getRPC()
{
	return m_rpc;
}

bool	NetworkModule::isConnected()	const
{
	return m_connected;
}
