#include "PlayerManager.h"
#include "NetworkID.h"
#include "NetworkRPC.h"
#include "BitStream.h"
#include "ServerCore.h"

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_players.insert(std::pair<ecs::NetworkID, ecs::Entity*>(currentPlayer->getNetworkID(), currentPlayer));
}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
}

void PlayerManager::addPlayer(ecs::Entity* newPlayer)
{
	m_players[newPlayer->getNetworkID()] = newPlayer;
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		RakNet::BitStream	bits;

		if (it->first == newPlayer->getNetworkID())
			continue;

		bits.WriteCompressed(newPlayer->getNetworkID());
		ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_ADD, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

bool PlayerManager::hasPlayer(ecs::NetworkID netID)
{
	return m_players.find(netID) != m_players.end();
}

void PlayerManager::removePlayer(ecs::NetworkID netID)
{
	m_players.erase(netID);

	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		RakNet::BitStream bits;

		if (it->first == netID)
			continue;

		bits.Write(netID);
		ServerCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::PLAYER_REMOVE, &bits, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, it->first, false);
	}
}

void PlayerManager::setCurrentPlayer(ecs::Entity* newCurrentPlayer)
{
	if (m_players[newCurrentPlayer->getNetworkID()] == nullptr)
	{
		m_currentPlayer = newCurrentPlayer;
		m_players.insert(std::pair<ecs::NetworkID, ecs::Entity*>(newCurrentPlayer->getNetworkID(), newCurrentPlayer));
	}
	else
	{
		m_currentPlayer = newCurrentPlayer;
		m_players[newCurrentPlayer->getNetworkID()] = newCurrentPlayer;
	}
}

ecs::Entity* PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}
