#include "SpawnerManager.h"
#include "WeaponCreator.h"
#include "WeaponManager.h"
#include "Life.h"
#include "Weapon.h"
#include "Armor.h"

SpawnerManager::SpawnerManager()
{

}

SpawnerManager::~SpawnerManager()
{

}

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

	if (dynamic_cast<ecs::Life*>((*entity)[ecs::AComponent::ComponentType::LIFE]) != nullptr)
	{
		if (i <= 5)
			dynamic_cast<ecs::Life*>((*entity)[ecs::AComponent::ComponentType::LIFE])->set(20);
		else if (i >= 6 && i <= 8)
			dynamic_cast<ecs::Life*>((*entity)[ecs::AComponent::ComponentType::LIFE])->set(40);
		else
			dynamic_cast<ecs::Life*>((*entity)[ecs::AComponent::ComponentType::LIFE])->set(100);
	}
}

void SpawnerManager::armorRegeneration(ecs::Entity* entity)
{
	int i = rand() % 5 + 1;

	if (dynamic_cast<ecs::Armor*>((*entity)[ecs::AComponent::ComponentType::ARMOR]) != nullptr)
	{
		if (i <= 4)
			dynamic_cast<ecs::Armor*>((*entity)[ecs::AComponent::ComponentType::ARMOR])->set(40);
		else
			dynamic_cast<ecs::Armor*>((*entity)[ecs::AComponent::ComponentType::ARMOR])->set(100);
	}
}

void SpawnerManager::weaponRegeneration(ecs::Entity* entity)
{
	int i = rand() % 10;
	(*entity)[ecs::AComponent::ComponentType::WEAPON] = &WeaponCreator::getInstance().create((const ecs::Weapon::WeaponType)i);
}

void SpawnerManager::pickObject(ecs::Entity* spawner, ecs::Entity* player)
{
	switch (spawner->getEntityType())
	{
	case ecs::Entity::EntityType::LIFE_SPAWNER :
		if (dynamic_cast<ecs::Life*>((*player)[ecs::AComponent::ComponentType::LIFE]) != nullptr && dynamic_cast<ecs::Life*>((*player)[ecs::AComponent::ComponentType::LIFE]) != nullptr)
		{
			dynamic_cast<ecs::Life*>((*player)[ecs::AComponent::ComponentType::LIFE])->restore(dynamic_cast<ecs::Life*>((*spawner)[ecs::AComponent::ComponentType::LIFE])->get());
			dynamic_cast<ecs::Life*>((*spawner)[ecs::AComponent::ComponentType::LIFE])->set(0);
		}
	case ecs::Entity::EntityType::ARMOR_SPAWNER :
		if (dynamic_cast<ecs::Armor*>((*player)[ecs::AComponent::ComponentType::ARMOR]) != nullptr && dynamic_cast<ecs::Armor*>((*player)[ecs::AComponent::ComponentType::ARMOR]) != nullptr)
		{
			dynamic_cast<ecs::Armor*>((*player)[ecs::AComponent::ComponentType::ARMOR])->restore(dynamic_cast<ecs::Armor*>((*spawner)[ecs::AComponent::ComponentType::ARMOR])->get());
			dynamic_cast<ecs::Armor*>((*spawner)[ecs::AComponent::ComponentType::ARMOR])->set(0);
		}
	case ecs::Entity::EntityType::WEAPON_SPAWNER :
		if (dynamic_cast<ecs::WeaponManager*>((*player)[ecs::AComponent::ComponentType::WEAPON_MANAGER]) != nullptr && dynamic_cast<ecs::Weapon*>((*spawner)[ecs::AComponent::ComponentType::WEAPON]) != nullptr)
		{
			dynamic_cast<ecs::WeaponManager*>((*player)[ecs::AComponent::ComponentType::WEAPON_MANAGER])->addWeapon(*dynamic_cast<ecs::Weapon*>((*spawner)[ecs::AComponent::ComponentType::WEAPON]));
			(*spawner)[ecs::AComponent::ComponentType::WEAPON] = nullptr;
		}
	}
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