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

	private:
		const std::string	NAME;
		const ComponentType	TYPE;
	};
}