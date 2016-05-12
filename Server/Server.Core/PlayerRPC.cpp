#include <irrlicht.h>
#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "ServerCore.h"
#include "PlayerFactory.h"
#include "Logger.h"

PlayerRPC::PlayerRPC()
{
	ServerCore::getInstance().getNetworkModule().getRPC()->RegisterFunction(NetworkRPC::PLAYER_CONNECT.c_str(), &PlayerRPC::playerConnect);
	ServerCore::getInstance().getNetworkModule().getRPC()->RegisterFunction(NetworkRPC::PLAYER_SYNC.c_str(), &PlayerRPC::playerSync);
}

PlayerRPC::~PlayerRPC()
{
	ServerCore::getInstance().getNetworkModule().getRPC()->UnregisterFunction(NetworkRPC::PLAYER_CONNECT.c_str());
	ServerCore::getInstance().getNetworkModule().getRPC()->UnregisterFunction(NetworkRPC::PLAYER_SYNC.c_str());
}

/*
** A la connexion d'un player
** Ajoute le joueur au pool du serveur et envoie l'info aux autres clients
** Renvoie au client son playerId affecté
*/
void	PlayerRPC::playerConnect(RakNet::BitStream* bitStream, RakNet::RPC3* remote)
{
	RakNet::RakString	name;
	RakNet::RakString	serial;
	static int		playerId;
	RakNet::BitStream	bits;

	bitStream->Read(name);
	bitStream->Read(serial);

	LOG_INFO(NETWORK) << "Received player name " << name.C_String() << " Serial(" << serial.C_String() << ")";
	ecs::Entity* player =  PlayerFactory::createPlayer(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), playerId, 0, 100);

	bits.WriteCompressed(playerId);
	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_CONNECT, this, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, remote->GetLastSenderAddress(), false);

	if (!ServerCore::getInstance().getPlayerManager().hasEntity(playerId))
	{
		//ServerCore::getInstance().getPlayerManager()->addPlayer(player);
	}
	++playerId;
}

/*
** Quand on reçoit les infos de synchronisation d'UN joueur
** Reçoit les infos, met à jour sur le serveur et envoie à tout le monde
*/
void	PlayerRPC::playerSync(RakNet::BitStream* bitStream, RakNet::RPC3* remote)
{
	ecs::PlayerId	playerId;

	bitStream->ReadCompressed(playerId);
	LOG_INFO(NETWORK) << "Received sync for player " << playerId;
}
