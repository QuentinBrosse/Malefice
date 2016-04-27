#pragma once

#include "StdInc.h"
#include "CollectionComponent.h"

namespace ecs
{
	class AComponent
	{
	public:
		AComponent(const std::string& name, ComponentType type);
		AComponent(const AComponent& component) = delete;
		~AComponent() = default;

		virtual void dump() const = 0;

	public:
		const std::string	NAME;
		const ComponentType	TYPE;
	};
}