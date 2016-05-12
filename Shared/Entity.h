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
		enum EntityType
		{
			NOTHING,
			PLAYER,
			SPAWN,
			MAP,
			ENTITY_COUNT,
		};

	public:
		const int	ID;

		Entity(NetworkID netID, const EntityType entityType);
		~Entity();
		Entity(const Entity& cpy) = delete;
		Entity(Entity &&) = default;
		
		Entity&	operator=(const Entity&) = delete;
		Entity&	operator=(Entity&&) = default;

		AComponent*&	operator[](ComponentType type);
		bool			has(ComponentType type);

		void			dump()			const;

		NetworkID		getNetworkID()	const;
		void			setNetworkID(const NetworkID networkId);
	private:
		const EntityType						ENTITY_TYPE;

		NetworkID								m_networkID;
		std::map<ComponentType, AComponent*>	m_components;
	};
}
