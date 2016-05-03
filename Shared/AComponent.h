#pragma once

#include <string>
#include <iostream>
#include "CollectionComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT AComponent
	{
	public:
		AComponent(const std::string& name, ComponentType type);
		AComponent(const AComponent& component) = delete;
		virtual ~AComponent() = default;

		virtual void dump() const = 0;

	public:
		const std::string	NAME;
		const ComponentType	TYPE;
	};
}
