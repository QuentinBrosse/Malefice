#include "Chat.h"
#include "ClientCore.h"
#include "NetworkRPC.h"
#include "BitStream.h"

void	Chat::sendNetworkMessage(ecs::NetworkID playerId, const std::string& message)
{
	RakNet::BitStream bits;
	RakNet::RakString input;
	
	if (ClientCore::getInstance().getNetworkModule()->isConnected() == false)
		return;

	input.Set(message.c_str());
	bits.Write(input);
	bits.WriteCompressed(playerId);

	//ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_CHAT, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, false);
}
