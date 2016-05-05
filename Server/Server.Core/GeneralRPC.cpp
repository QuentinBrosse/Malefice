#include "GeneralRPC.h"

#include "NetworkRPC.h"

#include "NetworkID.h"

#include "Logger.h"

#include "ServerCore.h"

bool	GeneralRPC::m_isRegistered = false;

/*
** Reçoit un message, l'affiche dans la console et le renvoie aux autres joueurs
*/
static void playerChat(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID		playerId = (ecs::NetworkID)packet->guid.systemIndex;
	RakNet::RakString	input;

	bitStream->Read(input);

	std::cout << "(" << playerId << ") : " << input.C_String() << std::endl;

	RakNet::BitStream toSend;
	toSend.WriteCompressed(playerId);
	toSend.Write(input);
	ServerCore::getInstance().getNetworkModule()->callRPC(RPC_CHAT_SEND, &toSend, HIGH_PRIORITY, RELIABLE_ORDERED, playerId, true);
}

void	GeneralRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;

	rpc->RegisterFunction(RPC_CHAT_RECEIVE, playerChat);
	m_isRegistered = true;
}

void	GeneralRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	m_isRegistered = false;
}
