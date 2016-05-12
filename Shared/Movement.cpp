#include "Movement.h"

namespace ecs
{
	Movement::Movement(const Position& position) : AComponent("Movement", MOVEMENT),
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
		os << "Movement {}";
	}
}
