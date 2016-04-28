
#include "PlayerRPC.h"

bool	PlayerRPC::m_bRegistered = false;

/*
A la connexion d'un player
Ajoute le joueur au pool du serveur et envoie l'info aux autres clients
*/
void PlayerConnect(RakNet::BitStream *pBitstream, RakNet::Packet *pPacket)
{
	RakNet::RakString sName;
	RakNet::RakString sSerial;

	pBitstream->Read(sName);
	pBitstream->Read(sSerial);

	std::cout << "Received player name " << sName.C_String() << " Serial(" << sSerial.C_String() << ")" << std::endl;
}

/*
A la déconnexion normale d'un player (Pas de crash)
Retire le joueur du pool du serveur et envoie l'info aux autres clients
*/
void PlayerDisconnect(RakNet::BitStream *pBitstream, RakNet::Packet *pPacket)
{

}

/*
Quand on reçoit les infos de synchronisation d'UN joueur
Reçoit les infos, met à jour sur le serveur et envoie à tout le monde
*/
void PlayerSync(RakNet::BitStream *pBitstream, RakNet::Packet *pPacket)
{

}

void	PlayerRPC::Register(RakNet::RPC4 * pRPC)
{
	if (m_bRegistered)
		return;

	pRPC->RegisterFunction(RPC_CONNECT, PlayerConnect);
	pRPC->RegisterFunction(RPC_DISCONNECT, PlayerDisconnect);
	pRPC->RegisterFunction(RPC_SYNC, PlayerSync);

	m_bRegistered = true;
}

void	PlayerRPC::Unregister(RakNet::RPC4 * pRPC)
{
	if (!m_bRegistered)
		return;

	pRPC->UnregisterFunction(RPC_CONNECT);
	pRPC->UnregisterFunction(RPC_DISCONNECT);
	pRPC->UnregisterFunction(RPC_SYNC);
	m_bRegistered = false;
}