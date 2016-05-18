#pragma once

#include <ostream>
#include <map>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	typedef RakNet::SystemIndex	ClientId;

	class MALEFICE_DLL_EXPORT Entity
	{
	public:
		enum class EntityType : int
		{
			NOTHING,
			PLAYER,
			SPAWN,
			MAP,
			ENTITY_COUNT,
		};

		Entity();
		Entity(ecs::ClientId owner, EntityType entityType);
		virtual ~Entity();
		Entity(const Entity&)	= delete;
		Entity(Entity&&)		= default;
		
		Entity&	operator=(const Entity&)	= delete;
		Entity&	operator=(Entity&&)			= default;
		

		bool										has(ecs::AComponent::ComponentType type)	const;
		ecs::ClientId								getOwner()				const;
		ecs::Entity::EntityType						getEntityType()			const;
		const std::map<ecs::AComponent::ComponentType, AComponent*>&	getComponents()			const;

		AComponent*&	operator[](ecs::AComponent::ComponentType type);
		void			setOwner(ecs::ClientId owner);
		void			setEntityType(ecs::Entity::EntityType entityType);
		void			addComponent(ecs::AComponent::ComponentType componentType, ecs::AComponent* component);


	private:
		ecs::ClientId							m_owner;
		EntityType								m_entityType;
		std::map<ecs::AComponent::ComponentType, AComponent*>	m_components;
	};
}

MALEFICE_DLL_EXPORT	std::ostream&		operator<<(std::ostream& os, const ecs::Entity& entity);

namespace RakNet
{
	MALEFICE_DLL_EXPORT RakNet::BitStream&	operator<<(RakNet::BitStream& out, ecs::Entity& in);
	MALEFICE_DLL_EXPORT RakNet::BitStream&	operator>>(RakNet::BitStream& in, ecs::Entity& out);
}
