#include "GeneralRPC.h"
#include "NetworkRPC.h"
#include "Logger.h"

bool	GeneralRPC::m_isRegistered = false;

static void	playerChat(RakNet::BitStream* userData, RakNet::Packet* packet)
{
	RakNet::RakString	message;

	userData->Read(message);
	LOG_INFO(CHAT) << "Received message: " << message.C_String();
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
