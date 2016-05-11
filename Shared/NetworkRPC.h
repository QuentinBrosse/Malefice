#pragma once

#include <string>
#include <RakNetTypes.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkRPC
{
public:
	NetworkRPC()	= delete;
	~NetworkRPC()	= delete;

	static const RakNet::NetworkID	GENERAL_RPC_ID;
	static const RakNet::NetworkID	PLAYER_RPC_ID;


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
