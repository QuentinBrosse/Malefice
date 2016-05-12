#include <iostream>
#include "Entity.h"

namespace ecs
{
	static int nextID()
	{
		static int id = 0;
		return id++;
	}

	Entity::Entity(NetworkID netID, const EntityType entityType) :
		ID(nextID()), m_networkID(netID), ENTITY_TYPE(entityType)
	{
	}

	Entity::~Entity()
	{
		for (auto component : m_components)
		{
			delete component.second;
		}
	}

	AComponent*& Entity::operator[](ComponentType type)
	{
		return m_components[type];
	}

	bool Entity::has(ComponentType type)
	{
		try
		{
			m_components.at(type);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	void Entity::dump() const
	{
		std::cout << "{ Entity " << ID << std::endl;
		for (auto component : m_components)
		{
			component.second->dump();
		}
		std::cout << "}" << std::endl;
	}

	NetworkID Entity::getNetworkID() const
	{
		return m_networkID;
	}

	void Entity::setNetworkID(const NetworkID networkId)
	{
		m_networkID = networkId;
	}

}