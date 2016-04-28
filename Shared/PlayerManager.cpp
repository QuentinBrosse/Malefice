#include "PlayerManager.h"

void PlayerManager::addPlayer(ecs::Entity *newPlayer)
{
	ecs::NetworkID*	componentNetworkID;

	if ((componentNetworkID = reinterpret_cast<ecs::NetworkID*>((*newPlayer)[ecs::NETWORK_ID])) != NULL)
		m_mPlayers[componentNetworkID->ID] = newPlayer;
}

void PlayerManager::removePlayer(const networkID netID)
{
	ecs::NetworkID*	componentNetworkID = reinterpret_cast<ecs::NetworkID*>((*m_mPlayers[netID])[ecs::NETWORK_ID]);

	if (componentNetworkID)
	{
		m_mPlayers.erase(netID);
		delete (componentNetworkID);
	}
}
