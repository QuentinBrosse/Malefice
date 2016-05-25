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

	void	Armor::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		Life::serialize(out, serializeType);
	}

	void	Armor::deserialize(RakNet::BitStream& in)
	{
		Life::deserialize(in);
	}


	AComponent&	Armor::affect(const AComponent& rhs)
	{
		const Armor&	armor = dynamic_cast<const Armor&>(rhs);

		m_currentLife = armor.m_currentLife;
		m_maxLife = armor.m_maxLife;
		return *this;
	}

	AComponent*	Armor::createCopy(const AComponent* rhs) const
	{
		const Armor* armor = dynamic_cast<const Armor*>(rhs);
		return new Armor(*armor);
	}
}
