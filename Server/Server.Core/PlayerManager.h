#pragma once

#include <map>
#include "Entity.h"
#include "Export.h"

class PlayerManager
{
public:
	PlayerManager();
	PlayerManager(ecs::Entity* currentPlayer);
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager() = default;

	void			addPlayer(ecs::Entity* newPlayer);
	void			removePlayer(ecs::PlayerId owner);

	bool			hasPlayer(ecs::PlayerId owner);

	void			setCurrentPlayer(ecs::Entity* newCurrentPlayer);
	ecs::Entity*	getCurrentPlayer() const;
private:
	std::map<ecs::PlayerId, ecs::Entity*>	m_players;
	ecs::Entity*							m_currentPlayer;
};
#pragma once
