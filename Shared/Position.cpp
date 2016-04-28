#include "Position.h"

namespace ecs
{
	Position::Position(float x, float y, float z): AComponent("Position", POSITION),
		m_iX(x), m_iY(y), m_iZ(z)
	{

	}

	Position::Position(const Position& pos) : AComponent("Position", POSITION),
		m_iX(pos.m_iX), m_iY(pos.m_iY), m_iZ(pos.m_iZ)
	{
		
	}

	Position& Position::operator=(const Position& pos)
	{
		m_iX = pos.m_iX;
		m_iY = pos.m_iY;
		m_iZ = pos.m_iZ;
		return *this;
	}

	void Position::set(float x, float y, float z)
	{
		m_iX = x;
		m_iY = y;
		m_iZ = z;
	}
	
	void Position::set(const Position& pos)
	{
		m_iX = pos.m_iX;
		m_iY = pos.m_iY;
		m_iZ = pos.m_iZ;
	}

	void Position::add(float x, float y, float z)
	{
		m_iX += x;
		m_iY += y;
		m_iZ += z;
	}

	void Position::add(const Position& pos)
	{
		m_iX += pos.m_iX;
		m_iY += pos.m_iY;
		m_iZ += pos.m_iZ;
	}

	void Position::sub(float x, float y, float z)
	{
		m_iX -= x;
		m_iY -= y;
		m_iZ -= z;
	}

	void Position::sub(const Position& pos)
	{
		m_iX -= pos.m_iX;
		m_iY -= pos.m_iY;
		m_iZ -= pos.m_iZ;
	}

	void Position::dump() const
	{
		std::cout << "[Position (" << m_iX << ", " << m_iY << ", "
			<< m_iZ << ")]" << std::endl;
	}

	float Position::getX() const
	{
		return m_iX;
	}

	float Position::getY() const
	{
		return m_iY;
	}

	float Position::getZ() const
	{
		return m_iZ;
	}

	Position Position::operator+(const Position& pos) const
	{
		return Position(m_iX + pos.m_iX, m_iY + pos.m_iY, m_iZ + pos.m_iZ);
	}

	Position Position::operator-(const Position& pos) const
	{
		return Position(m_iX - pos.m_iX, m_iY - pos.m_iY, m_iZ - pos.m_iZ);
	}

	Position& Position::operator+=(const Position& pos)
	{
		m_iX += pos.m_iX;
		m_iY += pos.m_iY;
		m_iZ += pos.m_iZ;
		return *this;
	}

	Position& Position::operator-=(const Position& pos)
	{
		m_iX -= pos.m_iX;
		m_iY -= pos.m_iY;
		m_iZ -= pos.m_iZ;
		return *this;
	}

}