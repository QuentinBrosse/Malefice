#include "PlayerRPC.h"

bool	PlayerRPC::m_isRegistered = false;

/*
** A la connexion d'un player
** Ajoute le joueur au pool du serveur et envoie l'info aux autres clients
*/
static void	playerConnect(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	RakNet::RakString sName;
	RakNet::RakString sSerial;

	bitStream->Read(sName);
	bitStream->Read(sSerial);

	std::cout << "Received player name " << sName.C_String() << " Serial(" << sSerial.C_String() << ")" << std::endl;
}

/*
** A la déconnexion normale d'un player (pas de crash)
** Retire le joueur du pool du serveur et envoie l'info aux autres clients
*/
static void	playerDisconnect(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{

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
	rpc->RegisterFunction(RPC_DISCONNECT, &playerDisconnect);
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
