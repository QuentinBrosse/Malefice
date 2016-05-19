#pragma once

#include "EntityManager.h"
#include "Singleton.h"
#include "Entity.h"

// TODO: do we really need a PlayerManager or is an EntityManager enough?
class PlayerManager : public EntityManager, public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

protected:
	PlayerManager();
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager()					= default;

public:
	ecs::Entity*	getCurrentPlayer()	const;
	void			setCurrentPlayer(ecs::Entity* localPlayer);
private:
	ecs::Entity*	m_currentPlayer;
};
