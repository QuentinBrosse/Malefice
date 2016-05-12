#pragma once

// Server Version

#include <map>
#include "Entity.h"
#include "Export.h"
#include "EntityManager.h"

class PlayerManager : public EntityManager
{
public:
	PlayerManager();
	PlayerManager(ecs::Entity* currentPlayer);
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager() = default;

	virtual void addEntity(ecs::Entity * newPlayer);
	virtual bool hasEntity(ecs::PlayerId owner);

	virtual void removeEntity(ecs::PlayerId owner);


	void			setCurrentPlayer(ecs::Entity* newCurrentPlayer);
	ecs::Entity*	getCurrentPlayer() const;
private:
	ecs::Entity*							m_currentPlayer;
};
