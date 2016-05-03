#pragma once

#include <map>
#include "Entity.h"
#include "Export.h"

class MALEFICE_DLL_EXPORT PlayerManager
{
public:
	PlayerManager()						= default;
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	void	addPlayer(ecs::Entity* newPlayer);
	void	removePlayer(unsigned int netID);


private:
	std::map<unsigned int, ecs::Entity*>	m_players;
	ecs::Entity*							m_currentPlayer;
};
