#include "AComponent.h"

namespace ecs
{
	AComponent::AComponent(const std::string& name, ecs::AComponent::ComponentType type) :
		NAME(name), TYPE(type)
	{
	}


	AComponent& AComponent::operator=(const AComponent & rhs)
	{
		return affect(rhs);
	}

	void	AComponent::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		if (serializeType)
			out.Write(TYPE);
	}

	void	AComponent::deserialize(RakNet::BitStream& in)
	{
	}
}

std::ostream&	operator<<(std::ostream& os, const ecs::AComponent& component)
{
	component.dump(os);
	return os;
}
