#pragma once

#include <map>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Entity
	{
	public:
		const int	ID;

		Entity();
		~Entity();
		Entity(const Entity& cpy);
		Entity(Entity &&) = default;
		
		Entity&	operator=(const Entity&) = delete;
		Entity&	operator=(Entity&&) = default;

		AComponent*&	operator[](ComponentType type);
		bool			has(ComponentType type);

		void	dump() const;


	private:
		std::map<ComponentType, AComponent*>	m_components;
	};
}
