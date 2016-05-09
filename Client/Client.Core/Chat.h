#pragma once

#include <string>
#include "Singleton.h"
#include "NetworkID.h"

class Chat : public Singleton<Chat>
{
	friend class Singleton<Chat>;

public:
	Chat()	= default;
	~Chat()	= default;

	void		sendNetworkMessage(ecs::NetworkID playerId, const std::string& message);
};
