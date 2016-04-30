#include "PlayerManager.h"
#include "NetworkID.h"

void PlayerManager::addPlayer(ecs::Entity *newPlayer)
{
	ecs::NetworkID*	componentNetworkID;

	if ((componentNetworkID = dynamic_cast<ecs::NetworkID*>((*newPlayer)[ecs::NETWORK_ID])) != NULL)
		m_players[componentNetworkID->ID] = newPlayer;
}

void PlayerManager::removePlayer(const unsigned int netID)
{
	ecs::NetworkID*	componentNetworkID = dynamic_cast<ecs::NetworkID*>((*m_players[netID])[ecs::NETWORK_ID]);

	if (componentNetworkID)
	{
		m_players.erase(netID);
		delete (componentNetworkID);
	}
}
