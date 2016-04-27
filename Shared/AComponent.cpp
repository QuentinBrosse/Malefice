#include "AComponent.h"

namespace ecs
{
	AComponent::AComponent(const std::string& name, ComponentType type): 
		NAME(name), TYPE(type)
	{

	}
}