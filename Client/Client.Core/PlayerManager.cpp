#include "PlayerManager.h"
#include "NetworkRPC.h"

PlayerManager::PlayerManager(ecs::Entity* currentPlayer)
{
	m_currentPlayer = currentPlayer;
	m_entities.insert(std::pair<ecs::PlayerId, ecs::Entity*>(currentPlayer->getOwner(), currentPlayer));
}

PlayerManager::~PlayerManager()
{

}

PlayerManager::PlayerManager()
{
	m_currentPlayer = nullptr;
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
