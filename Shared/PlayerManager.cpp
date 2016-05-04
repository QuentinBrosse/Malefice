#include "PlayerManager.h"
#include "NetworkID.h"

void PlayerManager::addPlayer(ecs::Entity *newPlayer)
{
	// A voir si il faut tester avant de l'ajouté
	m_players[newPlayer->getNetworkID()] = newPlayer;
}

void PlayerManager::removePlayer(ecs::NetworkID netID)
{
	m_players.erase(netID);		
}
