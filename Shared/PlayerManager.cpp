#include "PlayerManager.h"
#include "NetworkID.h"
#include "NetworkRPC.h"

#ifdef _SERVER
#include "../Server/Server.Core/ServerCore.h"
#endif

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_players.insert(std::pair<ecs::NetworkID, ecs::Entity*>(currentPlayer->getNetworkID(), currentPlayer));
}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
}

void PlayerManager::addPlayer(ecs::Entity *newPlayer)
{
	// A voir si il faut tester avant de l'ajouter
	m_players[newPlayer->getNetworkID()] = newPlayer;

#ifdef _SERVER
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		RakNet::BitStream *bits;

		bits.WriteCompressed(newPlayer->getNetworkID());
		bits.Write(RakNet::RakString("Test"));
		ServerCore::getInstance().getNetworkModule()->callRPC(RPC_CONNECT, &bits, HIGH_PRIORITY, RELIABLE, it->first, false);
	}
#endif
}

bool PlayerManager::hasPlayer(ecs::NetworkID netID)
{
	return m_players.find(netID) != m_players.end();
}

void PlayerManager::removePlayer(ecs::NetworkID netID)
{
	m_players.erase(netID);

#ifdef _SERVER
	for (auto it = m_players.begin(); it != m_players.end(); it++)
	{
		Raknet::BitStream *bits;

		bits.Write(netID);
		ServerCore::getInstance().getNetworkModule()->callRPC(RPC_DISCONNECT, &bits, HIGH_PRIORITY, RELIABLE, it->first, false);
	}
#endif
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
