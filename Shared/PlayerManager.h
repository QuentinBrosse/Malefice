#pragma once

#include <map>
#include "Entity.h"
#include "Export.h"
#include "NetworkID.h"

class MALEFICE_DLL_EXPORT PlayerManager
{
public:
	PlayerManager()						= default;
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	void	addPlayer(ecs::Entity* newPlayer);
	void	removePlayer(ecs::NetworkID netID);


private:
	std::map<ecs::NetworkID, ecs::Entity*>	m_players;
	ecs::Entity*							m_currentPlayer;
};
