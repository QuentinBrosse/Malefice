#include <iostream>
#include "ClientCore.h"

void ClientCore::addEntity(const ecs::Entity& newEntity)
{
	m_entities.insert(std::pair<const int, ecs::Entity> (newEntity.ID, newEntity));
}

void ClientCore::deleteEntity(int id)
{
	m_entities.erase(id);
}

void ClientCore::dump()	const
{
	for (auto pair : m_entities)
	{
		pair.second.dump();
		std::cout << std::endl;
	}
}
