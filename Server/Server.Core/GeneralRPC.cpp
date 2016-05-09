#include "GeneralRPC.h"
#include "NetworkRPC.h"
#include "NetworkID.h"
#include "Logger.h"
#include "ServerCore.h"

bool	GeneralRPC::m_isRegistered = false;

/*
** Reçoit un message, l'affiche dans la console et le renvoie aux autres joueurs
*/
static void	playerChat(RakNet::BitStream* bitStream, RakNet::Packet* packet)
{
	ecs::NetworkID		playerId = static_cast<ecs::NetworkID>(packet->guid.systemIndex);
	RakNet::RakString	input;

	bitStream->Read(input);

	LOG_INFO(CHAT) << "Player " << playerId << " : " << input.C_String();

	RakNet::BitStream toSend;
	toSend.WriteCompressed(playerId);
	toSend.Write(input);
	ServerCore::getInstance().getNetworkModule()->callRPC(RPC_CHAT, &toSend, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, RakNet::UNASSIGNED_PLAYER_INDEX, true);
}

void	GeneralRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(RPC_CHAT, &playerChat);
	m_isRegistered = true;
}

void	GeneralRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(RPC_CHAT);
	m_isRegistered = false;
}
