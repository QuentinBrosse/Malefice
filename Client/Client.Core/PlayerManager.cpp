#include "PlayerManager.h"
#include "ClientCore.h"
#include "PlayerFactory.h"
#include "PositionSystem.h"
#include "PlayerInfos.h"
#include "WeaponManagerSystem.h"
#include "SpellManagerSystem.h"
#include "WeaponManager.h"
#include "GraphicUtil.h"
#include "SceneAnimatedMesh.h"

PlayerManager::PlayerManager() : EntityManager(NetworkRPC::ReservedNetworkIds::PlayerManager)
{
}

void	PlayerManager::addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	ecs::Entity*	localEntity = new ecs::Entity(*entity);

	EntityManager::addEntity(owner, localEntity, rpc);

	if (ClientCore::getInstance().getClientId() == owner)
	{
		this->setCurrentPlayer(localEntity);
	}
}

void	PlayerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);

	for (auto& pair : m_entities)
	{
		ecs::PositionSystem::updateScenePosition(*pair.second);
	}
}

void	PlayerManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		ecs::Entity&	entity = *it->second;

		ecs::AScene*	scene = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE]);
		scene->getNode()->remove();
		m_entities.erase(it);
		LOG_INFO(ECS) << "Removed player entity with owner ID = " << owner << ".";
	}
	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}

void PlayerManager::initPlayersScene()
{
	irr::IrrlichtDevice* device = GraphicUtil::getInstance().getDevice();

	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		ecs::Team*	team = dynamic_cast<ecs::Team*>((*it->second)[ecs::AComponent::ComponentType::TEAM]);
		if (!team)
			continue;
		if (team->getTeam() == ecs::Team::TeamType::Predator)
			PlayerFactory::initScene(GraphicUtil::getInstance().getDevice(), "sydney.bmp", "sydney.md2", *it->second);
		else if (team->getTeam() == ecs::Team::TeamType::Team1)
			PlayerFactory::initScene(GraphicUtil::getInstance().getDevice(), "sydney_t1.bmp", "sydney.md2", *it->second);
		else
			PlayerFactory::initScene(GraphicUtil::getInstance().getDevice(), "sydney_t2.bmp", "sydney.md2", *it->second);
		ecs::PositionSystem::updateScenePosition(*it->second);

		if (it->second != m_currentPlayer)
		{
			ecs::SceneAnimatedMesh* scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*it->second)[ecs::AComponent::ComponentType::SCENE]);

			PlayerFactory::initNicknameNode(it->second, device, scene->getNode());
		}
	}
}

void PlayerManager::initPlayersWeapons()
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		if (dynamic_cast<ecs::Team*>((*it->second)[ecs::AComponent::ComponentType::TEAM])->getTeam() == ecs::Team::TeamType::Predator)
		{
			if (ClientCore::getInstance().getClientId() == it->first)
				ecs::SpellManagerSystem::initFPSScene(*it->second);
		}
		else
		{
			if (ClientCore::getInstance().getClientId() == it->first)
				ecs::WeaponManagerSystem::initFPSWeapon(*it->second);
			else
				ecs::WeaponManagerSystem::initExternalWeapon(*it->second);
		}
	}
}

ecs::Entity*	PlayerManager::getCurrentPlayer() const
{
	return m_currentPlayer;
}

void PlayerManager::setCurrentPlayer(ecs::Entity * localPlayer)
{
	m_currentPlayer = localPlayer;
}

const std::map<ecs::ClientId, ecs::Entity*> &PlayerManager::getEntities() const
{
	return m_entities;
}

int				PlayerManager::getTeam1Score()
{
	int			score = 0;

	for (auto &entity : m_entities)
	{
		ecs::Team *team = dynamic_cast<ecs::Team *>(entity.second);
		if (team != nullptr && team->getTeam() == ecs::Team::TeamType::Team1)
			score += team->getKills();
	}
	return score;
}

int				PlayerManager::getTeam2Score()
{
	int			score = 0;

	for (auto &entity : m_entities)
	{
		ecs::Team *team = dynamic_cast<ecs::Team *>(entity.second);
		if (team != nullptr && team->getTeam() == ecs::Team::TeamType::Team2)
			score += team->getKills();
	}
	return score;
}

int				PlayerManager::getPredatorScore()
{
	int			score = 0;

	for (auto &entity : m_entities)
	{
		ecs::Team *team = dynamic_cast<ecs::Team *>(entity.second);
		if (team != nullptr && team->getTeam() == ecs::Team::TeamType::Predator)
			score += team->getKills();
	}
	return score;
}

void PlayerManager::loadNormalTeamTexture()
{
	for (auto& entity : m_entities)
	{
		ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*entity.second)[ecs::AComponent::ComponentType::SCENE]);
		ecs::Team*				team = dynamic_cast<ecs::Team*>((*entity.second)[ecs::AComponent::ComponentType::TEAM]);
		if (scene != nullptr && team != nullptr)
		{
			ecs::Team::TeamType	teamType = team->getTeam();

			switch (teamType)
			{
			case ecs::Team::TeamType::Team1:
				scene->deleteTexture();
				scene->setTexture("sydney_t1.bmp");
				break;
			case ecs::Team::TeamType::Team2:
				scene->deleteTexture();
				scene->setTexture("sydney_t2.bmp");
				break;
			default:
				break;
			}
		}
	}
}

void PlayerManager::loadInvertTeamTexture()
{
	for (auto& entity : m_entities)
	{
		ecs::SceneAnimatedMesh*	scene = dynamic_cast<ecs::SceneAnimatedMesh*>((*entity.second)[ecs::AComponent::ComponentType::SCENE]);
		ecs::Team*				team = dynamic_cast<ecs::Team*>((*entity.second)[ecs::AComponent::ComponentType::TEAM]);
		if (scene != nullptr && team != nullptr)
		{
			ecs::Team::TeamType	teamType = team->getTeam();

			switch (teamType)
			{
			case ecs::Team::TeamType::Team1:
				scene->deleteTexture();
				scene->setTexture("sydney_t2.bmp");
				break;
			case ecs::Team::TeamType::Team2:
				scene->deleteTexture();
				scene->setTexture("sydney_t1.bmp");
				break;
			default:
				break;
			}
		}
	}
}
