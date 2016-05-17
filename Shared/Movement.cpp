#include "Movement.h"

namespace ecs
{
	Movement::Movement() : AComponent("Movement", ecs::AComponent::ComponentType::MOVEMENT),
		m_destination()
	{
	}

	Movement::Movement(const Position& position) : AComponent("Movement", ecs::AComponent::ComponentType::MOVEMENT),
		m_destination(position)
	{
	}

	void Movement::setDestination(const Position& newDestination)
	{
		m_destination = newDestination;
	}

	const Position& Movement::getDestination() const
	{
		return m_destination;
	}


	void Movement::move(Position& startPosition) const
	{
		if (m_destination != startPosition)
			startPosition = m_destination;
	}


	void	Movement::dump(std::ostream& os)	const
	{
		os << "Movement {destination = " << m_destination << "}";
	}


	void	Movement::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Movement::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
