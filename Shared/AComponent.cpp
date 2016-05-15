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


RakNet::BitStream&	RakNet::operator<<(RakNet::BitStream& out, ecs::AComponent& in)
{
	in.serialize(out);
	return out;
}

RakNet::BitStream&	RakNet::operator>>(RakNet::BitStream& in, ecs::AComponent& out)
{
	out.deserialize(in);
	return in;
}
