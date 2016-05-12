#pragma once

#include <ostream>
#include <string>
#include "NetworkObject.h"
#include "CollectionComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT AComponent
	{
	public:
		const std::string	NAME;
		const ComponentType	TYPE;

		AComponent(const std::string& name, ComponentType type);
		AComponent(const AComponent& component)	= delete;
		virtual ~AComponent()					= default;

		virtual void	dump(std::ostream& os)	const	= 0;
	};
}

MALEFICE_DLL_EXPORT	std::ostream&	operator<<(std::ostream& os, const ecs::AComponent& component);
