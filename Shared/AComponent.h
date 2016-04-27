#pragma once

#include "StdInc.h"
#include "CollectionComponent.h"

namespace ecs
{
	class AComponent
	{
	public:
		AComponent(const std::string& name, ComponentType type);
		~AComponent() = default;

		virtual void dump() const = 0;

	private:
		const std::string	NAME;
		const ComponentType	TYPE;
	};
}