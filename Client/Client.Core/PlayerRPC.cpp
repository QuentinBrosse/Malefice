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
	LOG_INFO(NETWORK) << "Player ID (assigned by server): " << playerId;

	RakNet::BitStream	bs;
	bs.Write(RakNet::RakString("Hello, World!"));
	ClientCore::getInstance().getNetworkModule()->callRPC(RPC_CHAT, &bs, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, packet->systemAddress);
}

/*
** Lors de la connexion d'un nouveau joueur
*/
static void newPlayer(RakNet::BitStream *bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID	playerId;

	bitStream->Read(playerId);
	LOG_INFO(NETWORK) << "A new player joined server, his id is : " << playerId;
}

/*
** Lors de la déconnexion d'un joueur
*/
static void removePlayer(RakNet::BitStream *bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID	playerId;

	bitStream->Read(playerId);
	LOG_INFO(NETWORK) << "Player " << playerId << " disconnected..";
}

void PlayerRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(RPC_CONNECT, &playerConnect);
	rpc->RegisterFunction(RPC_NEWPLAYER, &newPlayer);
	rpc->RegisterFunction(RPC_REMOVEPLAYER, &removePlayer);
	m_isRegistered = true;
}

void PlayerRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(RPC_CONNECT);
	rpc->UnregisterFunction(RPC_NEWPLAYER);
	rpc->UnregisterFunction(RPC_REMOVEPLAYER);
	m_isRegistered = false;
}
