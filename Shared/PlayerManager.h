#pragma once

#include <map>
#include "Entity.h"
#include "Export.h"
#include "NetworkID.h"

class MALEFICE_DLL_EXPORT PlayerManager
{
public:
	PlayerManager()						= default;
	PlayerManager(ecs::Entity* currentPlayer);
	PlayerManager(const PlayerManager&)	= delete;
	~PlayerManager()					= default;

	void			addPlayer(ecs::Entity* newPlayer);
	void			removePlayer(ecs::NetworkID netID);

	void			setCurrentPlayer(ecs::Entity* newCurrentPlayer);
	ecs::Entity*	getCurrentPlayer() const;
private:
	std::map<ecs::NetworkID, ecs::Entity*>	m_players;
	ecs::Entity*							m_currentPlayer;
};
