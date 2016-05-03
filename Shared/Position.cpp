		#include <iostream>
#include "Position.h"

namespace ecs
{
	Position::Position(float xPosition, float yPosition, float zPosition, float xTarget, float yTarget, float zTarget) : AComponent("Position", POSITION),
		m_vectorPosition(irr::core::vector3df(xPosition, yPosition, zPosition)), m_vectorTarget(irr::core::vector3df(xTarget, yTarget, zTarget))
	{
	}

	Position::Position(const Position& pos) : AComponent("Position", POSITION),
		m_vectorPosition(irr::core::vector3df(pos.m_vectorPosition)), m_vectorTarget(irr::core::vector3df(pos.m_vectorTarget))
	{
		
	}

	Position& Position::operator=(const Position& pos)
	{
		m_vectorPosition = pos.m_vectorPosition;
		m_vectorTarget = pos.m_vectorTarget;

		return *this;
	}

	void Position::setVectorPosition(float x, float y, float z)
	{
		m_vectorPosition.set(x, y, z);
	}

	void Position::setVectorTarget(float x, float y, float z)
	{
		m_vectorTarget.set(x, y, z);
	}

	void Position::set(const Position& pos)
	{
		m_vectorPosition = pos.m_vectorPosition;
		m_vectorTarget = pos.m_vectorTarget;
	}

	irr::core::vector3df Position::getVectorPosition() const
	{
		return m_vectorPosition;
	}

	irr::core::vector3df Position::getVectorTarget() const
	{
		return m_vectorTarget;
	}

	void Position::dump() const
	{
		std::cout << "[" << NAME << ": {" << m_vectorPosition.X << ", " << m_vectorPosition.Y << ", " << m_vectorPosition.Z << "} \ {" << m_vectorTarget.X << ", " << m_vectorTarget.Y << ", " << m_vectorTarget.Z << "} ]" << std::endl;
	}

	bool Position::operator!=(const Position& other) const
	{
		return m_vectorPosition != other.m_vectorPosition || m_vectorTarget != other.m_vectorTarget;
	}

	bool Position::operator==(const Position& other) const
	{
		return m_vectorPosition == other.m_vectorPosition && m_vectorTarget == other.m_vectorTarget;
	}
}