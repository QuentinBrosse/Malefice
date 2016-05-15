#include "AComponent.h"

namespace ecs
{
	AComponent::AComponent(const std::string& name, ComponentType type) :
		NAME(name), TYPE(type)
	{
	}
}

std::ostream&	operator<<(std::ostream& os, const ecs::AComponent& component)
{
	component.dump(os);
	return os;
}
