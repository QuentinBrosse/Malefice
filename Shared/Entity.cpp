#include "Entity.h"

namespace ecs
{
	static int nextID()
	{
		static int id = 0;
		return id++;
	}

	Entity::Entity() :
		ID(nextID())
	{

	}

	Entity::Entity(const Entity & cpy) :
		ID(cpy.ID)
	{
		for (auto component : cpy.m_components)
			m_components.insert(component);
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

}