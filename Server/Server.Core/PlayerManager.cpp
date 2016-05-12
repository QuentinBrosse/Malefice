// Server Version

#include "PlayerManager.h"
#include "NetworkRPC.h"
#include "BitStream.h"
#include "ServerCore.h"

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_entities.insert(std::pair<ecs::NetworkID, ecs::Entity*>(currentPlayer->getNetworkID(), currentPlayer));
}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
}

void PlayerManager::addEntity(ecs::Entity* newPlayer)
{
	m_entities[newPlayer->getNetworkID()] = newPlayer;
	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		RakNet::BitStream	bits;

		if (it->first == newPlayer->getNetworkID())
			continue;

		bits.WriteCompressed(newPlayer->getNetworkID());
		//ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_ADD, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

bool PlayerManager::hasEntity(ecs::NetworkID netID)
{
	return m_entities.find(netID) != m_entities.end();
}

void PlayerManager::removeEntity(ecs::NetworkID netID)
{
	m_entities.erase(netID);

	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		RakNet::BitStream bits;

		if (it->first == netID)
			continue;

		bits.Write(netID);
		//ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_REMOVE, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

void PlayerManager::setCurrentPlayer(ecs::Entity* newCurrentPlayer)
{
	if (m_entities[newCurrentPlayer->getNetworkID()] == nullptr)
	{
		m_currentPlayer = newCurrentPlayer;
		m_entities.insert(std::pair<ecs::NetworkID, ecs::Entity*>(newCurrentPlayer->getNetworkID(), newCurrentPlayer));
	}
	else
	{
		m_currentPlayer = newCurrentPlayer;
		m_entities[newCurrentPlayer->getNetworkID()] = newCurrentPlayer;
	}
}

ecs::Entity* PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}
