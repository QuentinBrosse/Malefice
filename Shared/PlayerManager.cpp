#include "PlayerManager.h"

void PlayerManager::addPlayer(const ecs::Entity *newPlayer)
{
	NetworkID*	componentNetworkID;

	if ((componentNetworkID = newPlayer[NETWORK_ID]) != NULL)
		m_mPlayers.insert(std::pair<networkID, ecs::Entity*>(componentNetworkID.ID, newPlayer));
}

void PlayerManager::removePlayer(const networkID netId)
{
	NetworkID*	componentNetworkID = m_mPlayers[netID];

	if (componentNetworkID)
	{
		m_mPlayers.erase(netID)
		delete (componentNetworkID);
	}
}
