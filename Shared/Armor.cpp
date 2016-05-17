#include "Armor.h"
#include <iostream>

namespace ecs
{
	Armor::Armor() : Life(ecs::AComponent::ComponentType::ARMOR)
	{
	}

	Armor::Armor(int maxHP) : Life(maxHP, ecs::AComponent::ComponentType::ARMOR)
	{
	}


	void	Armor::dump(std::ostream& os)	const
	{
		os << "Armor:";
		Life::dump(os);
	}


	void	Armor::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Armor::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
