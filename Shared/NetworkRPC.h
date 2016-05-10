#pragma once

#include <string>
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkRPC
{
public:
	NetworkRPC()	= delete;
	~NetworkRPC()	= delete;

	// Local player
	static const std::string	PLAYER_CONNECT;
	static const std::string	PLAYER_DISCONNECT;
	static const std::string	PLAYER_SYNC;

	// Remote players
	static const std::string	PLAYER_ADD;
	static const std::string	PLAYER_REMOVE;
	
	// General
	static const std::string	PLAYER_CHAT;
};
