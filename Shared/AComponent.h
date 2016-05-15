#pragma once

#include <ostream>
#include <string>
#include <BitStream.h>
#include "CollectionComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT AComponent
	{
	public:
		const std::string	NAME;
		const ComponentType	TYPE;

		AComponent()							= default;
		AComponent(const std::string& name, ComponentType type);
		AComponent(const AComponent& component)	= delete;
		virtual ~AComponent()					= default;

		virtual void	dump(std::ostream& os)	const	= 0;

		virtual void	serialize(RakNet::BitStream& out)	const	= 0;
		virtual void	deserialize(RakNet::BitStream& in)			= 0;
	};
}

MALEFICE_DLL_EXPORT	std::ostream&	operator<<(std::ostream& os, const ecs::AComponent& component);
