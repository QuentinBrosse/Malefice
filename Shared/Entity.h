#pragma once

#include <ostream>
#include <map>
#include "NetworkObject.h"
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	typedef int	PlayerId;

	class MALEFICE_DLL_EXPORT Entity : public NetworkObject
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

		Entity(PlayerId owner, const EntityType entityType);
		~Entity();
		Entity(const Entity&)	= delete;
		Entity(Entity&&)		= default;
		
		Entity&	operator=(const Entity&)	= delete;
		Entity&	operator=(Entity&&)			= default;
		

		bool										has(ComponentType type)	const;
		PlayerId									getOwner()				const;
		const std::map<ComponentType, AComponent*>&	getComponents()			const;

		AComponent*&	operator[](ComponentType type);


	private:
		PlayerId								m_owner;
		const EntityType						ENTITY_TYPE;
		std::map<ComponentType, AComponent*>	m_components;
	};
}

MALEFICE_DLL_EXPORT	std::ostream&	operator<<(std::ostream& os, const ecs::Entity& entity);
