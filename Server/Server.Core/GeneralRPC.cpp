#include "GeneralRPC.h"
#include "NetworkRPC.h"
#include "Logger.h"
#include "ServerCore.h"

GeneralRPC::GeneralRPC()
{
	ServerCore::getInstance().getNetworkModule()->getRPC()->RegisterFunction(NetworkRPC::PLAYER_CHAT.c_str(), &GeneralRPC::playerChat);
}

GeneralRPC::~GeneralRPC()
{
	ServerCore::getInstance().getNetworkModule()->getRPC()->UnregisterFunction(NetworkRPC::PLAYER_CHAT.c_str());
}

/*
** Reçoit un message, l'affiche dans la console et le renvoie aux autres joueurs
*/
void	GeneralRPC::playerChat(RakNet::BitStream* bitStream, RakNet::RPC3* remote)
{
	int						playerId;
	RakNet::RakString		input;
	RakNet::BitStream		toSend;

	bitStream->ReadCompressed(playerId);
	bitStream->Read(input);
	LOG_INFO(CHAT) << "Player " << playerId << " : " << input.C_String();
	toSend.WriteCompressed(playerId);
	toSend.Write(input);
	ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_CHAT, this, &toSend, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}
