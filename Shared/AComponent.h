#pragma once

#include <ostream>
#include <string>
#include <BitStream.h>
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT AComponent
	{
	public:
		enum class ComponentType : int
		{
			LIFE,
			ARMOR,
			POSITION,
			MOVEMENT,
			TEAM,
			WEAPON,
			WEAPON_MANAGER,
			SPELL,
			SPELL_MANAGER,
			CAMERA,
			SCENE,
			GAME_EVENT_RECEIVER,
			PLAYER_INFOS,
			COMPONENT_COUNT
		};

		const std::string	NAME;
		const ecs::AComponent::ComponentType	TYPE;

		AComponent()							= default;
		AComponent(const std::string& name, ecs::AComponent::ComponentType type);
		AComponent(const AComponent& component)	= delete;
		virtual ~AComponent()					= default;

		virtual	void	dump(std::ostream& os)	const	= 0;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:

	};
}

MALEFICE_DLL_EXPORT	std::ostream&	operator<<(std::ostream& os, const ecs::AComponent& component);
