#include "Position.h"

namespace ecs
{
	Position::Position() : AComponent("Position", ecs::ComponentType::POSITION)
	{
	}

	Position::Position(float xPosition, float yPosition, float zPosition, float xRotation, float yRotation, float zRotation, float xScale, float yScale, float zScale) : AComponent("Position", POSITION),
		m_vectorPosition(irr::core::vector3df(xPosition, yPosition, zPosition)), m_vectorRotation(irr::core::vector3df(xRotation, yRotation, zRotation)), m_vectorScale(irr::core::vector3df(xScale, yScale, zScale))
	{
	}

	Position::Position(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const irr::core::vector3df& vectorScale): AComponent("Position", POSITION),
		m_vectorPosition(vectorPosition), m_vectorRotation(vectorRotation), m_vectorScale(vectorScale)
	{
	}

	Position::Position(const Position& pos) : AComponent("Position", POSITION),
		m_vectorPosition(irr::core::vector3df(pos.m_vectorPosition)), m_vectorRotation(irr::core::vector3df(pos.m_vectorRotation)), m_vectorScale(irr::core::vector3df(pos.m_vectorScale))
	{
		
	}

	Position& Position::operator=(const Position& pos)
	{
		m_vectorPosition = pos.m_vectorPosition;
		m_vectorRotation = pos.m_vectorRotation;
		m_vectorScale = pos.m_vectorScale;

		return *this;
	}

	void Position::setVectorPosition(const irr::core::vector3df& newVectorPosition)
	{
		m_vectorPosition.set(newVectorPosition);
	}

	void Position::setVectorRotation(const irr::core::vector3df& newVectorRotation)
	{
		m_vectorRotation.set(newVectorRotation);
	}

	void Position::setVectorScale(const irr::core::vector3df& newVectorScale)
	{
		m_vectorScale = newVectorScale;
	}

	void Position::set(const Position& pos)
	{
		m_vectorPosition = pos.m_vectorPosition;
		m_vectorRotation = pos.m_vectorRotation;
	}

	irr::core::vector3df Position::getVectorPosition() const
	{
		return m_vectorPosition;
	}

	irr::core::vector3df Position::getVectorRotation() const
	{
		return m_vectorRotation;
	}

	irr::core::vector3df Position::getVectorScale() const
	{
		return m_vectorScale;
	}

	void	Position::dump(std::ostream& os)	const
	{
		os << "[" << NAME << ": {" << m_vectorPosition.X << ", " << m_vectorPosition.Y << ", " << m_vectorPosition.Z << "} \ {" << m_vectorRotation.X << ", " << m_vectorRotation.Y << ", " << m_vectorRotation.Z << "} ]" << std::endl;
	}

	bool Position::operator!=(const Position& other) const
	{
		return m_vectorPosition != other.m_vectorPosition || m_vectorRotation != other.m_vectorRotation || m_vectorScale != other.m_vectorScale;
	}

	bool Position::operator==(const Position& other) const
	{
		return m_vectorPosition == other.m_vectorPosition && m_vectorRotation == other.m_vectorRotation && m_vectorScale == other.m_vectorScale;
	}


	void	Position::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Position::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}