#include "ClientCore.h"

void ClientCore::addEntity(const ecs::Entity& newEntity)
{
	m_entityes.insert(std::pair<const int, ecs::Entity> (newEntity.ID, newEntity));
}

void ClientCore::deleteEntity(const int id)
{
	m_entityes.erase(id);
}

void ClientCore::dump() const
{
	for (auto pair : m_entityes)
	{
		pair.second.dump();
		std::cout << std::endl;
	}
}
