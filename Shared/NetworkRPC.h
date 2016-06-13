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
		SpawnerManager,
		UnreservedStart,
		WeaponManagerSystem = RakNet::UNASSIGNED_NETWORK_ID,
		WeaponSystem = RakNet::UNASSIGNED_NETWORK_ID,
		SpellSystem = RakNet::UNASSIGNED_NETWORK_ID,
		LifeSystem = RakNet::UNASSIGNED_NETWORK_ID,
		SpellManagerSystem = RakNet::UNASSIGNED_NETWORK_ID,
	};


	// Client-Side executed

	static const std::string	CLIENT_CORE_SET_CLIENT_ID;
	static const std::string	CLIENT_CORE_NOTIFY_INVALID_NICKNAME;
	static const std::string	CLIENT_CORE_START_GAME;

	static const std::string	PLAYER_MANAGER_ADD_ENTITY;
	static const std::string	PLAYER_MANAGER_UPDATE_ENTITY;
	static const std::string	PLAYER_MANAGER_REMOVE_ENTITY;

	static const std::string	SPAWNER_MANAGER_ADD_ENTITY;
	static const std::string	SPAWNER_MANAGER_UPDATE_ENTITY;
	static const std::string	SPAWNER_MANAGER_REMOVE_ENTITY;
	static const std::string	SPAWNER_MANAGER_SET_VISIBILITY;
	static const std::string	LIFE_SYSTEM_DIE;

	static const std::string	TRIGGER_SHOOT_ACTIONS;

	static const std::string	CLIENT_CORE_STOP_GAME;

	// Server-Side executed

	static const std::string	PLAYER_MANAGER_SET_PLAYER_NICKNAME;
	static const std::string	PLAYER_MANAGER_SERVER_UPDATE_ENTITY;
	
	static const std::string	WEAPON_SYSTEM_SHOOT;
	static const std::string	WEAPON_SYSTEM_RELOAD;

	static const std::string	WEAPON_MANAGER_SYSTEM_CHANGE_NEXT;
	static const std::string	WEAPON_MANAGER_SYSTEM_CHANGE_PREC;

	static const std::string	SPELL_MANAGER_SYSTEM_CHANGE_NEXT;
	static const std::string	SPELL_MANAGER_SYSTEM_CHANGE_PREC;

	static const std::string	SPAWNER_MANAGER_COLLISION_DETECTION;
	static const std::string	SPELL_SYSTEM_LAUNCH_SPELL;
	static const std::string	SPAWNER_MANAGER_UPDATE_VISIBILITY;

	static const std::string	LIFE_SYSTEM_RESTORE;
	static const std::string	LIFE_SYSTEM_RESTORE_ARMOR;
};
