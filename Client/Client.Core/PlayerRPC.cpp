#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"
#include "ClientCore.h"
#include "Logger.h"
#include "Entity.h"
#include "PlayerFactory.h"

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
	ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_CHAT, &bs, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, packet->systemAddress);
}

/*
** Lors de la connexion d'un nouveau joueur
*/
static void addPlayer(RakNet::BitStream *bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID	playerId;

	bitStream->Read(playerId);
	LOG_INFO(NETWORK) << "A new player joined server, his id is: " << playerId;

	if (!ClientCore::getInstance().getPlayerManager()->hasPlayer(playerId))
	{
		ecs::Entity* player = PlayerFactory::createPlayer(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), playerId, 0, 100);
		ClientCore::getInstance().getPlayerManager()->addPlayer(player);
	}
}

/*
** Lors de la déconnexion d'un joueur
*/
static void removePlayer(RakNet::BitStream *bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID	playerId;

	bitStream->Read(playerId);
	LOG_INFO(NETWORK) << "Player " << playerId << " disconnected..";

	if (ClientCore::getInstance().getPlayerManager()->hasPlayer(playerId))
	{
		ClientCore::getInstance().getPlayerManager()->removePlayer(playerId);
	}
}

void PlayerRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(NetworkRPC::PLAYER_CONNECT.c_str(), &playerConnect);
	rpc->RegisterFunction(NetworkRPC::PLAYER_ADD.c_str(), &addPlayer);
	rpc->RegisterFunction(NetworkRPC::PLAYER_REMOVE.c_str(), &removePlayer);
	m_isRegistered = true;
}

void PlayerRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(NetworkRPC::PLAYER_CONNECT.c_str());
	rpc->UnregisterFunction(NetworkRPC::PLAYER_ADD.c_str());
	rpc->UnregisterFunction(NetworkRPC::PLAYER_REMOVE.c_str());
	m_isRegistered = false;
}
