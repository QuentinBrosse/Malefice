#pragma once

#include <map>
#include "AComponent.h"
#include "Export.h"
#include "NetworkID.h"

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

		void			dump()			const;

		NetworkID		getNetworkID()	const;
		void			setNetworkID(const NetworkID networkId);
	private:
		NetworkID								m_networkID;
		std::map<ComponentType, AComponent*>	m_components;
	};
}
