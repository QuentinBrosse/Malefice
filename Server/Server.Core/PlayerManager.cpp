#include "PlayerManager.h"
#include "NetworkRPC.h"
#include "BitStream.h"
#include "ServerCore.h"

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_players.insert(std::pair<ecs::PlayerId, ecs::Entity*>(currentPlayer->getOwner(), currentPlayer));
}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
}

void PlayerManager::addPlayer(ecs::Entity* newPlayer)
{
	m_players[newPlayer->getOwner()] = newPlayer;
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		RakNet::BitStream	bits;

		if (it->first == newPlayer->getOwner())
			continue;

		bits.WriteCompressed(newPlayer->getOwner());
		//ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_ADD, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

bool PlayerManager::hasPlayer(ecs::PlayerId owner)
{
	return m_players.find(owner) != m_players.end();
}

void PlayerManager::removePlayer(ecs::PlayerId owner)
{
	m_players.erase(owner);

	for (auto it = m_players.begin(); it != m_players.end(); it++)
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
	if (m_players[newCurrentPlayer->getOwner()] == nullptr)
	{
		m_currentPlayer = newCurrentPlayer;
		m_players.insert(std::pair<ecs::PlayerId, ecs::Entity*>(newCurrentPlayer->getOwner(), newCurrentPlayer));
	}
	else
	{
		m_currentPlayer = newCurrentPlayer;
		m_players[newCurrentPlayer->getOwner()] = newCurrentPlayer;
	}
}

ecs::Entity* PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}
