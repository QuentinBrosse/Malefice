#pragma once

#include "Entity.h"
#include "NetworkID.h"

class PlayerManager
{
public:
	PlayerManager() = default;
	PlayerManager(const PlayerManager&) = delete;
	~PlayerManager() = default;
	void	addPlayer(ecs::Entity* newPlayer);
	void	removePlayer(const networkID netID);
private:
	std::map<networkID, ecs::Entity*>	m_mPlayers;
	ecs::Entity*						m_cCurrentPlayer;
};