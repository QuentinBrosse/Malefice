#include "Position.h"
#include "IrrlichtUtility.h"

namespace ecs
{
	Position::Position() : AComponent("Position", ecs::AComponent::ComponentType::POSITION),
		m_vectorPosition(0.f, 0.f, 0.f), m_vectorRotation(0.f, 0.f, 0.f), m_vectorScale(0.f, 0.f, 0.f)
	{
	}

	Position::Position(float xPosition, float yPosition, float zPosition, float xRotation, float yRotation, float zRotation, float xScale, float yScale, float zScale) : AComponent("Position", ecs::AComponent::ComponentType::POSITION),
		m_vectorPosition(irr::core::vector3df(xPosition, yPosition, zPosition)), m_vectorRotation(irr::core::vector3df(xRotation, yRotation, zRotation)), m_vectorScale(irr::core::vector3df(xScale, yScale, zScale))
	{
	}

	Position::Position(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const irr::core::vector3df& vectorScale): AComponent("Position", ecs::AComponent::ComponentType::POSITION),
		m_vectorPosition(vectorPosition), m_vectorRotation(vectorRotation), m_vectorScale(vectorScale)
	{
	}

	Position::Position(const Position& pos) : AComponent("Position", ecs::AComponent::ComponentType::POSITION),
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


	bool Position::operator!=(const Position& other) const
	{
		return m_vectorPosition != other.m_vectorPosition || m_vectorRotation != other.m_vectorRotation || m_vectorScale != other.m_vectorScale;
	}

	bool Position::operator==(const Position& other) const
	{
		return m_vectorPosition == other.m_vectorPosition && m_vectorRotation == other.m_vectorRotation && m_vectorScale == other.m_vectorScale;
	}


	void	Position::dump(std::ostream& os)	const
	{
		os << "Position {vectorPosition = " << m_vectorPosition << ", vectorRotation = " << m_vectorRotation << ", vectorScale = " << m_vectorScale << "}";
	}


	void	Position::serialize(RakNet::BitStream& out)	const
	{
		AComponent::serialize(out);
		out.Write(m_vectorPosition.X);
		out.Write(m_vectorPosition.Y);
		out.Write(m_vectorPosition.Z);
		out.Write(m_vectorRotation.X);
		out.Write(m_vectorRotation.Y);
		out.Write(m_vectorRotation.Z);
		out.Write(m_vectorScale.X);
		out.Write(m_vectorScale.Y);
		out.Write(m_vectorScale.Z);
	}

	void	Position::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_vectorPosition.X);
		in.Read(m_vectorPosition.Y);
		in.Read(m_vectorPosition.Z);
		in.Read(m_vectorRotation.X);
		in.Read(m_vectorRotation.Y);
		in.Read(m_vectorRotation.Z);
		in.Read(m_vectorScale.X);
		in.Read(m_vectorScale.Y);
		in.Read(m_vectorScale.Z);
	}
}
