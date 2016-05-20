#include "SpawnerManager.h"
#include "WeaponCreator.h"
#include "Life.h"
#include "Weapon.h"
#include "Armor.h"

std::map<ecs::ClientId, ecs::Entity*> SpawnerManager::getSpawners() const
{
	return (m_spawners);
}

void SpawnerManager::add(ecs::Entity* newSpawner)
{
	m_spawners[newSpawner->getOwner()] = newSpawner;
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
	(*entity)[ecs::AComponent::ComponentType::WEAPON] = &WeaponCreator::getInstance().create((const ecs::Weapon::WeaponType)i);
}

void SpawnerManager::regenerate(ecs::ClientId owner)
{
	if (getSpawners()[owner])
	{
		if (getSpawners()[owner]->getEntityType() == ecs::Entity::EntityType::ARMOR_SPAWNER)
			armorRegeneration(getSpawners()[owner]);
		else if (getSpawners()[owner]->getEntityType() == ecs::Entity::EntityType::WEAPON_SPAWNER)
			weaponRegeneration(getSpawners()[owner]);
		else
			lifeRegeneration(getSpawners()[owner]);
	}
}

void SpawnerManager::remove(ecs::ClientId owner)
{
	if (m_spawners[owner])
		m_spawners.erase(owner);
}

ecs::Entity* SpawnerManager::seekSpawnerById(ecs::ClientId owner)
{
	if (m_spawners[owner])
		return (m_spawners[owner]);
	return(nullptr);
}

void SpawnerManager::dump() const
{
	return;
}