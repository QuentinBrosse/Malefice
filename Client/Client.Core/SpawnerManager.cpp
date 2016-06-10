#include "SpawnerManager.h"
#include "WeaponCreator.h"
#include "Life.h"
#include "Weapon.h"
#include "Armor.h"
#include "ClientCore.h"

//Client Side
SpawnerManager::SpawnerManager() : EntityManager(NetworkRPC::ReservedNetworkIds::SpawnerManager)
{
	m_inc = 0.F;
	first = true;
}

SpawnerManager::~SpawnerManager()
{

}

void SpawnerManager::addEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3 * rpc)
{
	ecs::Entity*	localEntity = new ecs::Entity(*entity);
	EntityManager::addEntity(owner, localEntity, rpc);
}

void	SpawnerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);

	for (auto& pair : m_entities)
	{
		ecs::PositionSystem::updateScenePosition(*pair.second);
	}
}

void	SpawnerManager::removeEntity(ecs::ClientId owner, RakNet::RPC3* rpc)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		ecs::Entity&	entity = *it->second;

		ecs::AScene*	scene = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE]);
		scene->getNode()->remove();
		m_entities.erase(it);
		LOG_INFO(ECS) << "Removed spawner entity with owner ID = " << owner << ".";
	}
	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}

void SpawnerManager::initSpawnersScene()
{
	irr::IrrlichtDevice* device = GraphicUtil::getInstance().getDevice();

	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		if (it->second->getEntityType() == ecs::Entity::EntityType::WEAPON_SPAWNER)
		{
			SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + dynamic_cast<ecs::Weapon*>((*it->second)[ecs::AComponent::ComponentType::WEAPON])->getMeshName()).c_str(), *it->second);
		}
		else if (it->second->getEntityType() == ecs::Entity::EntityType::LIFE_SPAWNER)
		{
			if (dynamic_cast<ecs::Life*>((*it->second)[ecs::AComponent::ComponentType::LIFE])->getMaxLife() == 20)
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("heart.obj")).c_str(), *it->second);
			else if (dynamic_cast<ecs::Life*>((*it->second)[ecs::AComponent::ComponentType::LIFE])->getMaxLife() == 50)
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("heart2.obj")).c_str(), *it->second);
			else
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("heart3.obj")).c_str(), *it->second);
		}
		else
		{
			if (dynamic_cast<ecs::Armor*>((*it->second)[ecs::AComponent::ComponentType::ARMOR])->getMaxLife() == 20)
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("armor.obj")).c_str(), *it->second);
			else if (dynamic_cast<ecs::Armor*>((*it->second)[ecs::AComponent::ComponentType::ARMOR])->getMaxLife() == 50)
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("armor2.obj")).c_str(), *it->second);
			else
				SpawnerFactory::initScene(GraphicUtil::getInstance().getDevice(), std::string(std::string("weapons/models/") + std::string("armor3.obj")).c_str(), *it->second);

		}
		ecs::PositionSystem::updateScenePosition(*it->second);
	}
}

void SpawnerManager::lifeRegeneration(ecs::Entity* entity)
{
	int i = rand() % 10 + 1;

	if (i <= 5)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(20, ecs::AComponent::ComponentType::LIFE);
	else if (i >= 6 && i <= 8)
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(40, ecs::AComponent::ComponentType::LIFE);
	else
		(*entity)[ecs::AComponent::ComponentType::LIFE] = new ecs::Life(100, ecs::AComponent::ComponentType::LIFE);
}

void SpawnerManager::armorRegeneration(ecs::Entity* entity)
{
	int i = rand() % 5 + 1;

	if (i <= 4)
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(40);
	else
		(*entity)[ecs::AComponent::ComponentType::ARMOR] = new ecs::Armor(100);
}

void SpawnerManager::weaponRegeneration(ecs::Entity* entity)
{
	int i = rand() % 10;
	// TODO: fix taking address of temporary:
	// (*entity)[ecs::AComponent::ComponentType::WEAPON] = &WeaponCreator::getInstance().create(static_cast<ecs::Weapon::WeaponType>(i));
}

void SpawnerManager::regenerate(ecs::ClientId owner)
{
	if (m_entities[owner])
	{
		if (m_entities[owner]->getEntityType() == ecs::Entity::EntityType::ARMOR_SPAWNER)
			armorRegeneration(m_entities[owner]);
		else if (m_entities[owner]->getEntityType() == ecs::Entity::EntityType::WEAPON_SPAWNER)
			weaponRegeneration(m_entities[owner]);
		else
			lifeRegeneration(m_entities[owner]);
	}
}

ecs::Entity* SpawnerManager::seekSpawnerById(ecs::ClientId owner)
{
	if (m_entities[owner])
		return (m_entities[owner]);
	return(nullptr);
}

void SpawnerManager::collisionDetection(ecs::Entity& entity)
{
	irr::core::aabbox3df boud = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE])->getNode()->getTransformedBoundingBox();
	
	for (auto& spawn : m_entities)
	{
		if (first)
		{
			first = false;
			break;
		}
		if (!dynamic_cast<ecs::AScene*>((*spawn.second)[ecs::AComponent::ComponentType::SCENE])->getNode()->isVisible())
			continue;
		irr::core::aabbox3df boudSpawn = dynamic_cast<ecs::AScene*>((*spawn.second)[ecs::AComponent::ComponentType::SCENE])->getNode()->getTransformedBoundingBox();

		if (boudSpawn.intersectsWithBox(boud))
			pickObject(spawn.second, &entity);
	}
}

void SpawnerManager::pickObject(ecs::Entity* spawner, ecs::Entity* player)
{
	switch (spawner->getEntityType())
	{
	case ecs::Entity::EntityType::LIFE_SPAWNER:
		if (dynamic_cast<ecs::Life*>((*player)[ecs::AComponent::ComponentType::LIFE]) != nullptr)
		{
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::LIFE_SYSTEM_RESTORE, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::LifeSystem), player, dynamic_cast<ecs::Life*>((*spawner)[ecs::AComponent::ComponentType::LIFE])->get());
			break;
		}
	case ecs::Entity::EntityType::ARMOR_SPAWNER:
		if (dynamic_cast<ecs::Armor*>((*player)[ecs::AComponent::ComponentType::ARMOR]) != nullptr)
		{
			ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::LIFE_SYSTEM_RESTORE_ARMOR, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::LifeSystem), player, dynamic_cast<ecs::Armor*>((*spawner)[ecs::AComponent::ComponentType::ARMOR])->get());
			break;
		}
	case ecs::Entity::EntityType::WEAPON_SPAWNER:
		if (dynamic_cast<ecs::WeaponManager*>((*player)[ecs::AComponent::ComponentType::WEAPON_MANAGER]) != nullptr && dynamic_cast<ecs::Weapon*>((*spawner)[ecs::AComponent::ComponentType::WEAPON]) != nullptr)
		{
			dynamic_cast<ecs::WeaponManager*>((*player)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->addWeapon(*dynamic_cast<ecs::Weapon*>((*spawner)[ecs::AComponent::ComponentType::WEAPON]));
			break;
		}
		else
			return;
	}
	ClientCore::getInstance().getNetworkModule()->callRPC(NetworkRPC::SPAWNER_MANAGER_UPDATE_VISIBILITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), spawner, false);
}

std::map<ecs::ClientId, ecs::Entity*> SpawnerManager::getSpawners() const
{
	return (m_entities);
}

void SpawnerManager::dump() const
{
	return;
}

void SpawnerManager::setSpawnerVisibility(ecs::Entity* player, const bool isVisible, RakNet::RPC3* rpc)
{
	ecs::Entity* entity = m_entities[player->getOwner()];
	dynamic_cast<ecs::SceneAnimatedMesh*>((*entity)[ecs::AComponent::ComponentType::SCENE])->getNode()->setVisible(isVisible);
}
