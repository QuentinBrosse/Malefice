#pragma once

#include <string>
#include <RakNetTypes.h>
#include "Export.h"

class MALEFICE_DLL_EXPORT NetworkRPC
{
public:
	NetworkRPC()	= delete;
	~NetworkRPC()	= delete;

	enum class ReservedNetworkIds : RakNet::NetworkID
	{
		None = 0,
		ClientCore,
		PlayerManager,
		UnreservedStart,
		WeaponSystem = RakNet::UNASSIGNED_NETWORK_ID
	};


	// Client-Side executed

	static const std::string	CLIENT_CORE_SET_CLIENT_ID;
	static const std::string	CLIENT_CORE_NOTIFY_INVALID_NICKNAME;
	static const std::string	CLIENT_CORE_START_GAME;

	static const std::string	PLAYER_MANAGER_ADD_ENTITY;
	static const std::string	PLAYER_MANAGER_UPDATE_ENTITY;
	static const std::string	PLAYER_MANAGER_REMOVE_ENTITY;


	// Server-Side executed

	static const std::string	PLAYER_MANAGER_SET_PLAYER_NICKNAME;
	static const std::string	PLAYER_MANAGER_SERVER_UPDATE_ENTITY;
	static const std::string	WEAPON_SYSTEM_SHOOT;
};
