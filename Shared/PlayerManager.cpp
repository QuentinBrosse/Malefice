#include "PlayerManager.h"

void PlayerManager::addPlayer(ecs::Entity *newPlayer)
{
	ecs::NetworkID*	componentNetworkID;

	if ((componentNetworkID = (*newPlayer)[ecs::NETWORK_ID]) != NULL)
		m_mPlayers[componentNetworkID] = newPlayer->ID;
}

void PlayerManager::removePlayer(const networkID netID)
{
	ecs::NetworkID*	componentNetworkID = (*m_mPlayers[netID])[ecs::NETWORK_ID];

	if (componentNetworkID)
	{
		m_mPlayers.erase(netID)
		delete (componentNetworkID);
	}
}
