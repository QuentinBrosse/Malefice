#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"
#include "ClientCore.h"
#include "Logger.h"
#include "Entity.h"
#include "PlayerFactory.h"
#include "SystemUtility.h"

PlayerRPC::PlayerRPC()
{
	this->SetNetworkIDManager(ClientCore::getInstance().getNetworkModule()->getNetworkIDManager());
	this->SetNetworkID(NetworkRPC::PLAYER_RPC_ID);
	ClientCore::getInstance().getNetworkModule()->getRPC()->RegisterFunction(NetworkRPC::PLAYER_CONNECT.c_str(), &PlayerRPC::playerConnect);
	ClientCore::getInstance().getNetworkModule()->getRPC()->RegisterFunction(NetworkRPC::PLAYER_ADD.c_str(), &PlayerRPC::addPlayer);
	ClientCore::getInstance().getNetworkModule()->getRPC()->RegisterFunction(NetworkRPC::PLAYER_REMOVE.c_str(), &PlayerRPC::removePlayer);
}

PlayerRPC::~PlayerRPC()
{
	ClientCore::getInstance().getNetworkModule()->getRPC()->UnregisterFunction(NetworkRPC::PLAYER_CONNECT.c_str());
	ClientCore::getInstance().getNetworkModule()->getRPC()->UnregisterFunction(NetworkRPC::PLAYER_ADD.c_str());
	ClientCore::getInstance().getNetworkModule()->getRPC()->UnregisterFunction(NetworkRPC::PLAYER_REMOVE.c_str());
}

void	PlayerRPC::connectionAccepted()
{
	RakNet::BitStream	bits;
	RakNet::RakString	username = "MALEFICE_PLAYER";
	RakNet::RakString	serial = utility::SystemUtility::getSerialHash().c_str();

	bits.Write(username);
	bits.Write(serial);
	ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_CONNECT, this, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED);
	LOG_DEBUG(NETWORK) << "Server accepted connection, sending username: \"" << username << "\", serial: \"" << serial << "\"";
}

/*
** Appelé par le serveur en retour de la demande de connexion
*/
void	PlayerRPC::playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote)
{
	int	playerId;

	bitStream->ReadCompressed(playerId);
	LOG_INFO(NETWORK) << "Player ID (assigned by server): " << playerId;

	RakNet::BitStream	bs;
	bs.WriteCompressed(playerId);
	bs.Write(RakNet::RakString("Hello, World!"));
	ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_CHAT, this, &bs, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED);
}

/*
** Lors de la connexion d'un nouveau joueur
*/
void	PlayerRPC::addPlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote)
{
	int	playerId;

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
void	PlayerRPC::removePlayer(RakNet::BitStream *bitStream, RakNet::RPC3* remote)
{
	ecs::NetworkID	playerId;

	bitStream->Read(playerId);
	LOG_INFO(NETWORK) << "Player " << playerId << " disconnected..";

	if (ClientCore::getInstance().getPlayerManager()->hasPlayer(playerId))
	{
		ClientCore::getInstance().getPlayerManager()->removePlayer(playerId);
	}
}
