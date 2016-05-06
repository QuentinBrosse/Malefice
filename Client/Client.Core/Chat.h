#pragma once

#include "Singleton.h"

#include "NetworkID.h"
#include "NetworkRPC.h"
#include "BitStream.h"

class Chat : public Singleton<Chat>
{
	friend class Singleton<Chat>;

public:
	Chat();
	~Chat();
	void		sendNetworkMessage(ecs::NetworkID playerId, std::string & message);
protected:

private:
};
