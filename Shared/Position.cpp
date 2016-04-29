#include "Position.h"

namespace ecs
{
	Position::Position(float x, float y, float z): AComponent("Position", POSITION),
		m_x(x), m_y(y), m_z(z)
	{

	}

	Position::Position(const Position& pos) : AComponent("Position", POSITION),
		m_x(pos.m_x), m_y(pos.m_y), m_z(pos.m_z)
	{
		
	}

	Position& Position::operator=(const Position& pos)
	{
		m_x = pos.m_x;
		m_y = pos.m_y;
		m_z = pos.m_z;
		return *this;
	}

	void Position::set(float x, float y, float z)
	{
		m_x = x;
		m_y = y;
		m_z = z;
	}
	
	void Position::set(const Position& pos)
	{
		m_x = pos.m_x;
		m_y = pos.m_y;
		m_z = pos.m_z;
	}

	void Position::add(float x, float y, float z)
	{
		m_x += x;
		m_y += y;
		m_z += z;
	}

	void Position::add(const Position& pos)
	{
		m_x += pos.m_x;
		m_y += pos.m_y;
		m_z += pos.m_z;
	}

	void Position::sub(float x, float y, float z)
	{
		m_x -= x;
		m_y -= y;
		m_z -= z;
	}

	void Position::sub(const Position& pos)
	{
		m_x -= pos.m_x;
		m_y -= pos.m_y;
		m_z -= pos.m_z;
	}

	void Position::dump() const
	{
		std::cout << "[Position (" << m_x << ", " << m_y << ", "
			<< m_z << ")]" << std::endl;
	}

	float Position::getX() const
	{
		return m_x;
	}

	float Position::getY() const
	{
		return m_y;
	}

	float Position::getZ() const
	{
		return m_z;
	}

	Position Position::operator+(const Position& pos) const
	{
		return Position(m_x + pos.m_x, m_y + pos.m_y, m_z + pos.m_z);
	}

	Position Position::operator-(const Position& pos) const
	{
		return Position(m_x - pos.m_x, m_y - pos.m_y, m_z - pos.m_z);
	}

	bool Position::operator==(const Position& pos) const
	{
		return m_x == pos.m_x && m_y == pos.m_y && m_z == pos.m_z;
	}

	bool Position::operator!=(const Position& pos) const
	{
		return m_x != pos.m_x || m_y != pos.m_y || m_z != pos.m_z;
	}

	Position& Position::operator+=(const Position& pos)
	{
		m_x += pos.m_x;
		m_y += pos.m_y;
		m_z += pos.m_z;
		return *this;
	}

	Position& Position::operator-=(const Position& pos)
	{
		m_x -= pos.m_x;
		m_y -= pos.m_y;
		m_z -= pos.m_z;
		return *this;
	}

}