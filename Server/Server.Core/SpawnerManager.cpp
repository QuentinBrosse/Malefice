#include "SpawnerManager.h"
#include "WeaponCreator.h"
#include "Life.h"
#include "Weapon.h"
#include "Armor.h"
#include "ServerCore.h"
#include "TimeUtility.h"
#include "ProjectGlobals.h"

//Serveur side
SpawnerManager::SpawnerManager() : EntityManager(), NetworkObject(NetworkRPC::ReservedNetworkIds::SpawnerManager)
{
	m_inc = 0.F;
	m_spawnPositionsWeapon.push_back(ecs::Position(irr::core::vector3df(80, -50, -300), irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(200.0, 200.0, 200.0)));
	m_spawnPositionsWeapon.push_back(ecs::Position(irr::core::vector3df(80, -50, -20), irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(200.0, 200.0, 200.0)));
	m_spawnPositionsWeapon.push_back(ecs::Position(irr::core::vector3df(80, -50, -150), irr::core::vector3df(0.0, 0.0, 0.0), irr::core::vector3df(200.0, 200.0, 200.0)));

	m_spawnPositionsLife.push_back(ecs::Position(irr::core::vector3df(80, -50, 80), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.1, 0.1, 0.1)));
	m_spawnPositionsLife.push_back(ecs::Position(irr::core::vector3df(80, -50, 30), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.1, 0.1, 0.1)));
	m_spawnPositionsLife.push_back(ecs::Position(irr::core::vector3df(80, -50, 5), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.1, 0.1, 0.1)));

	m_spawnPositionsArmor.push_back(ecs::Position(irr::core::vector3df(80, -50, 80), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.2, 0.2, 0.2)));
	m_spawnPositionsArmor.push_back(ecs::Position(irr::core::vector3df(80, -50, 30), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.2, 0.2, 0.2)));
	m_spawnPositionsArmor.push_back(ecs::Position(irr::core::vector3df(80, -50, 5), irr::core::vector3df(-90.0, 90.0, 0.0), irr::core::vector3df(0.2, 0.2, 0.2)));
}

void SpawnerManager::createEntity(ecs::ClientId owner)
{
	//creating Weapon Spawner
	for (std::list<ecs::Position>::iterator it = m_spawnPositionsWeapon.begin(); it != m_spawnPositionsWeapon.end(); ++it)
	{
		m_entities[owner] = SpawnerFactory::createWeaponSpawner(ServerCore::getInstance().getPhysicsUtil().getDevice(), (*it), owner);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_NETWORK_ID, true, owner, m_entities[owner]);
		owner++;
	}

	//creating Life Spawner
	for (std::list<ecs::Position>::iterator it = m_spawnPositionsLife.begin(); it != m_spawnPositionsLife.end(); ++it)
	{
		m_entities[owner] = SpawnerFactory::createLifeSpawner(ServerCore::getInstance().getPhysicsUtil().getDevice(), (*it), owner);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_NETWORK_ID, true, owner, m_entities[owner]);
		owner++;
	}

	//creating Armor spawner
	for (std::list<ecs::Position>::iterator it = m_spawnPositionsArmor.begin(); it != m_spawnPositionsArmor.end(); ++it)
	{
		m_entities[owner] = SpawnerFactory::createArmorSpawner(ServerCore::getInstance().getPhysicsUtil().getDevice(), (*it), owner);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_ADD_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_NETWORK_ID, true, owner, m_entities[owner]);
		owner++;
	}
}

void SpawnerManager::updateEntities()
{
	checkTimer();
	for (auto& entity : m_entities)
	{
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_UPDATE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, entity.second->getOwner(), entity.second);
	}
}

void SpawnerManager::deleteEntity(ecs::ClientId owner)
{
	auto	it = m_entities.find(owner);

	if (it != m_entities.end())
	{
		ecs::Entity&	entity = *it->second;

		ecs::AScene*	scene = dynamic_cast<ecs::AScene*>(entity[ecs::AComponent::ComponentType::SCENE]);
		scene->getNode()->remove();
		m_entities.erase(it);
		ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_REMOVE_ENTITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, owner);
		LOG_INFO(ECS) << "Deleted spawner entity with owner ID = " << owner << ".";
	}

	else
	{
		LOG_ERROR(ECS) << "Could not delete entity with owner = " << owner << " (not found).";
	}
}

void SpawnerManager::updateEntity(ecs::ClientId owner, ecs::Entity* entity, RakNet::RPC3* rpc)
{
	EntityManager::updateEntity(owner, entity, rpc);
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
	//(*entity)[ecs::AComponent::ComponentType::WEAPON] = &WeaponCreator::getInstance().create(static_cast<ecs::Weapon::WeaponType>(i));
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
	return nullptr;
}

std::map<ecs::ClientId, ecs::Entity*> SpawnerManager::getSpawners() const
{
	return (m_entities);
}

void SpawnerManager::dump() const
{
	return;
}

void SpawnerManager::setSpawnerVisibility(ecs::Entity* spawner, const bool isVisible, RakNet::RPC3* rpc)
{
	if (!isVisible)
		m_timer[spawner->getOwner()] = utility::TimeUtility::getMsTime() + (1000 * ProjectGlobals::getSpawnerVisibilityTimer());
	ServerCore::getInstance().getNetworkModule().callRPC(NetworkRPC::SPAWNER_MANAGER_SET_VISIBILITY, static_cast<RakNet::NetworkID>(NetworkRPC::ReservedNetworkIds::SpawnerManager), RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, spawner, isVisible);
}

void SpawnerManager::checkTimer()
{
	long long currentTime = utility::TimeUtility::getMsTime();

	for (auto& time : m_timer)
	{
		if (time.second <= currentTime && time.second != 0)
		{
			time.second = 0;
			setSpawnerVisibility(m_entities[time.first], true, nullptr);
		}
	}
}
