#include "GeneralRPC.h"
#include "NetworkRPC.h"
#include "ClientCore.h"
#include "Logger.h"

GeneralRPC::GeneralRPC()
{
	ClientCore::getInstance().getNetworkModule()->getRPC()->RegisterFunction(NetworkRPC::PLAYER_CHAT.c_str(), &GeneralRPC::playerChat);
}

GeneralRPC::~GeneralRPC()
{
	ClientCore::getInstance().getNetworkModule()->getRPC()->UnregisterFunction(NetworkRPC::PLAYER_CHAT.c_str());
}

void	GeneralRPC::playerChat(RakNet::BitStream* userData, RakNet::RPC3* remote)
{
	int					playerId;
	RakNet::RakString	message;

	userData->ReadCompressed(playerId);
	userData->Read(message);
	LOG_INFO(CHAT) << "Message from player " << playerId << ": " << message.C_String();
}
