#include "Chat.h"

#include "ClientCore.h"

Chat::Chat()
{

}

Chat::~Chat()
{

}

void	Chat::sendNetworkMessage(ecs::NetworkID playerId, std::string& message)
{
	RakNet::BitStream bits;
	RakNet::RakString input;
	
	if (ClientCore::getInstance().getNetworkModule()->isConnected() == false)
		return;

	input.Set(message.c_str());
	bits.Write(input);
	bits.WriteCompressed(playerId);

	ClientCore::getInstance().getNetworkModule()->callRPC(RPC_CHAT_RECEIVE, &bits, HIGH_PRIORITY, RELIABLE, false);
}