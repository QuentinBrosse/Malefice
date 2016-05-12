#pragma once

// Client Version

#include <map>

#include "EntityManager.h"
#include "Export.h"
#include "NetworkID.h"

class PlayerManager : public EntityManager
{
public:
	PlayerManager();
	PlayerManager(ecs::Entity* currentPlayer);
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager();

	void			setCurrentPlayer(ecs::Entity* newCurrentPlayer);
	ecs::Entity*	getCurrentPlayer() const;
private:
	ecs::Entity*							m_currentPlayer;
};
