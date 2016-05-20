#include <RakNetTypes.h>
#include "PlayerManager.h"
#include "PlayerFactory.h"
#include "PlayerInfos.h"
#include "Team.h"
#include "ServerCore.h"
#include "NetworkRPC.h"
#include "Logger.h"
#include "ProjectGlobals.h"

PlayerManager::PlayerManager() : NetworkObject(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}


void	PlayerManager::createEntity(ecs::ClientId owner)
{
	ecs::Team::TeamType	team = ecs::Team::TeamType::TEAM_COUNT;

	if (m_entities.size() < ProjectGlobals::NORMAL_TEAM_SIZE)
		team = ecs::Team::TeamType::Team1;
	else if (m_entities.size() < 2 * ProjectGlobals::NORMAL_TEAM_SIZE)
		team = ecs::Team::TeamType::Team2;
	else
		team = ecs::Team::TeamType::Predator;
	if (team != ecs::Team::TeamType::Predator)
		m_entities[owner] = PlayerFactory::createPlayer(owner, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), team, 100); // TODO: pick random spawn position, set rotation
	else
		m_entities[owner] = PlayerFactory::createPredator(owner, irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0)); // TODO: pick random spawn position, set rotation
	// Don't send new player to anyone yet, wait for the username (C.F. below)
}

void	PlayerManager::updateEntities()
{
	for (auto entity : m_entities)
	{
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_UPDATE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity.second->getOwner(), entity.second);
	}
}

void	PlayerManager::deleteEntity(ecs::ClientId owner)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		m_entities.erase(it);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_REMOVE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, owner);
	}

	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}


bool	PlayerManager::isNicknameAvailable(const std::string& nickname)	const
{
	for (auto entity : m_entities)
	{
		ecs::Entity&	player = *entity.second;

		ecs::PlayerInfos*	playerInfos = dynamic_cast<ecs::PlayerInfos*>(player[ecs::AComponent::ComponentType::PLAYER_INFOS]);

		if (nickname == playerInfos->getNickname())
			return false;
	}
	return true;
}


void	PlayerManager::setPlayerNickname(RakNet::RakString nickname, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(rpc->GetLastSenderAddress().systemIndex);

	if (!this->isNicknameAvailable(nickname.C_String()))
	{
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::CLIENT_CORE_NOTIFY_INVALID_NICKNAME, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::ClientCore), rpc->GetLastSenderAddress().systemIndex, false);
		return;
	}
	if (it != m_entities.end())
	{
		ecs::PlayerInfos*	playerInfos	= dynamic_cast<ecs::PlayerInfos*>((*it->second)[ecs::AComponent::ComponentType::PLAYER_INFOS]);

		playerInfos->setNickname(nickname.C_String());
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), rpc->GetLastSenderAddress().systemIndex, true, it->second->getOwner(), it->second);

		for (auto entity : m_entities)
		{
			ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::PLAYER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::PlayerManager), rpc->GetLastSenderAddress().systemIndex, false, entity.second->getOwner(), entity.second);
		}
		LOG_DEBUG(ECS) << "Set nickname of client " << rpc->GetLastSenderAddress().systemIndex << " to \"" << playerInfos->getNickname() << "\"";
	
		if (m_entities.size() == 3/*ProjectGlobals::MAX_PLAYERS_NB*/)
			ServerCore::getInstance().startGame();
	}

	else
	{
		LOG_ERROR(ECS) << "Could not set player nickname with owner = " << rpc->GetLastSenderAddress().systemIndex << " (not found).";
	}
}
