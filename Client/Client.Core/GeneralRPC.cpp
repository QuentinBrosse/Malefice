#include "GeneralRPC.h"
#include "NetworkRPC.h"
#include "Logger.h"
#include "NetworkID.h"

bool	GeneralRPC::m_isRegistered = false;

static void	playerChat(RakNet::BitStream* userData, RakNet::Packet* packet)
{
	ecs::NetworkID		playerId;
	RakNet::RakString	message;

	userData->ReadCompressed(playerId);
	userData->Read(message);
	LOG_INFO(CHAT) << "Message from player " << playerId << ": " << message.C_String();
}

void GeneralRPC::registerRPC(RakNet::RPC4* rpc)
{
	if (m_isRegistered)
		return;
	rpc->RegisterFunction(RPC_CHAT, &playerChat);
	m_isRegistered = true;
}

void GeneralRPC::unregisterRPC(RakNet::RPC4* rpc)
{
	if (!m_isRegistered)
		return;
	rpc->UnregisterFunction(RPC_CHAT);
	m_isRegistered = false;
}
