#include "PlayerRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"

bool	PlayerRPC::m_isRegistered = false;

/*
** Appelé par le serveur en retour de la demande de connexion
*/
static void	playerConnect(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID playerId;

	bitStream->ReadCompressed(playerId);

	std::cout << "Mon id affecté par le serveur est " << playerId << std::endl;
}

void PlayerRPC::registerRPC(RakNet::RPC4* rpc)
{
	rpc->RegisterFunction(RPC_CONNECT, &playerConnect);

	m_isRegistered = true;
}

void PlayerRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	rpc->UnregisterFunction(RPC_CONNECT);

	m_isRegistered = false;
}