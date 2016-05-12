#include <iostream>
#include "Entity.h"

namespace ecs
{
	Entity::Entity(PlayerId owner, const EntityType entityType) : NetworkObject(),
		m_owner(owner), m_components(), ENTITY_TYPE(entityType)
	{
	}

	Entity::~Entity()
	{
		for (auto component : m_components)
		{
			delete component.second;
		}
	}



	bool	Entity::has(ComponentType type)	const
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

	PlayerId	Entity::getOwner()	const
	{
		return m_owner;
	}

	const std::map<ComponentType, AComponent*>&	Entity::getComponents()	const
	{
		return m_components;
	}


	AComponent*&	Entity::operator[](ComponentType type)
	{
		return m_components[type];
	}
}

std::ostream&	operator<<(std::ostream& os, const ecs::Entity& entity)
{
	auto&	components = entity.getComponents();

	os << "Entity {owner = " << entity.getOwner() << ", components = [";
	for (auto component : components)
	{
		os << *(component.second);
	}
	os << "]}";
	return os;
}
