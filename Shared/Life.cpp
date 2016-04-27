#include "Life.h"

namespace ecs
{
	Life::Life(int max_life) : AComponent("Life", LIFE),
		m_iCurrent(max_life), MAX(max_life)
	{

	}

	int Life::get() const
	{
		return m_iCurrent;
	}

	void Life::set(int life)
	{
		if (life < 0)
		{
			// Error can't have negative life.
		}
		if (life > MAX)
		{
			// Set to max Life ? Or throw exception ?
		}
		m_iCurrent = life;
		if (m_iCurrent == 0)
		{
			onDeath();
		}
	}

	void Life::takeDamage(int damage)
	{
		if (damage < 0)
		{
			// Heal ? Or throw exception ?
		}
		m_iCurrent -= damage;
		if (m_iCurrent <= 0)
		{
			m_iCurrent = 0;
			onDeath();
		}
	}

	void Life::onDeath()
	{
		// Death behavior ...
	}

	void Life::dump() const
	{
		std::cout << "[Life " << m_iCurrent << "/" << MAX << "]" << std::endl;
	}
}