// Server Version

#include "PlayerManager.h"
#include "NetworkRPC.h"
#include "BitStream.h"
#include "ServerCore.h"

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_entities.insert(std::pair<ecs::PlayerId, ecs::Entity*>(currentPlayer->getOwner(), currentPlayer));
}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
}

void PlayerManager::addEntity(ecs::Entity* newPlayer)
{
	m_entities[newPlayer->getOwner()] = newPlayer;
	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		RakNet::BitStream	bits;

		if (it->first == newPlayer->getOwner())
			continue;

		bits.WriteCompressed(newPlayer->getOwner());
		//ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_ADD, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

bool PlayerManager::hasEntity(ecs::PlayerId owner)
{
	return m_entities.find(owner) != m_entities.end();
}

void PlayerManager::removeEntity(ecs::PlayerId owner)
{
	m_entities.erase(owner);

	for (auto it = m_entities.begin(); it != m_entities.end(); it++)
	{
		RakNet::BitStream bits;

		if (it->first == owner)
			continue;

		bits.Write(owner);
		//ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_REMOVE, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

void PlayerManager::setCurrentPlayer(ecs::Entity* newCurrentPlayer)
{
	if (m_entities[newCurrentPlayer->getOwner()] == nullptr)
	{
		m_currentPlayer = newCurrentPlayer;
		m_entities.insert(std::pair<ecs::PlayerId, ecs::Entity*>(newCurrentPlayer->getOwner(), newCurrentPlayer));
	}
	else
	{
		m_currentPlayer = newCurrentPlayer;
		m_entities[newCurrentPlayer->getOwner()] = newCurrentPlayer;
	}
}

ecs::Entity* PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}
