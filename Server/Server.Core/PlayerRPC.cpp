#include <iostream>
#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"

#include "ServerCore.h"

#include "Logger.h"

#include "PlayerFactory.h"
#include "Entity.h"
#include "PlayerManager.h"

bool	PlayerRPC::m_isRegistered = false;

/*
** A la connexion d'un player
** Ajoute le joueur au pool du serveur et envoie l'info aux autres clients
** Renvoie au client son playerId affecté
*/
static void	playerConnect(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	RakNet::RakString	name;
	RakNet::RakString	serial;
	ecs::NetworkID		playerId;

	bitStream->Read(name);
	bitStream->Read(serial);
	playerId = static_cast<ecs::NetworkID>(packet->guid.systemIndex);

	LOG_INFO(NETWORK) << "Received player name " << name.C_String() << " Serial(" << serial.C_String() << ")";

	ecs::Entity* player =  PlayerFactory::createPlayer(0, 0, 0, 0, 0, 0, playerId, 0, 100);
	ServerCore::getInstance().getPlayerManager()->addPlayer(player);
}

/*
** Quand on reçoit les infos de synchronisation d'UN joueur
** Reçoit les infos, met à jour sur le serveur et envoie à tout le monde
*/
static void	playerSync(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{

}


void	PlayerRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(RPC_CONNECT, &playerConnect);
	rpc->RegisterFunction(RPC_SYNC, &playerSync);
	m_isRegistered = true;
}

void	PlayerRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(RPC_CONNECT);
	rpc->UnregisterFunction(RPC_DISCONNECT);
	rpc->UnregisterFunction(RPC_SYNC);
	m_isRegistered = false;
}
