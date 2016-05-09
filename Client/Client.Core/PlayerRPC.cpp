#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"
#include "ClientCore.h"
#include "Logger.h"

bool	PlayerRPC::m_isRegistered = false;

/*
** Appelé par le serveur en retour de la demande de connexion
*/
static void	playerConnect(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID playerId;

	bitStream->ReadCompressed(playerId);
	LOG_DEBUG(NETWORK) << "Player ID (assigned by server): " << playerId;

	RakNet::BitStream	bs;
	bs.Write("Hello, World!");
	ClientCore::getInstance().getNetworkModule()->callRPC(RPC_CHAT, &bs, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, false);
}

void PlayerRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(RPC_CONNECT, &playerConnect);
	m_isRegistered = true;
}

void PlayerRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(RPC_CONNECT);
	m_isRegistered = false;
}
