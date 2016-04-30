#include <iostream>
#include "Life.h"

namespace ecs
{
	Life::Life(int maxLife) : AComponent("Life", LIFE),
		m_currentLife(maxLife), MAX_LIFE(maxLife)
	{

	}

	int Life::get() const
	{
		return m_currentLife;
	}

	void Life::set(int life)
	{
		if (life < 0)
		{
			// Error can't have negative life.
		}
		if (life > MAX_LIFE)
		{
			// Set to max Life ? Or throw exception ?
		}
		m_currentLife = life;
		if (m_currentLife == 0)
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
		m_currentLife -= damage;
		if (m_currentLife <= 0)
		{
			m_currentLife = 0;
			onDeath();
		}
	}

	void Life::restore(int quantity)
	{
		m_currentLife += quantity;
		if (m_currentLife > MAX_LIFE)
			m_currentLife = MAX_LIFE;
	}

	void Life::onDeath()
	{
		// Death behavior ...
	}

	void Life::dump() const
	{
		std::cout << "[Life " << m_currentLife << "/" << MAX_LIFE<< "]" << std::endl;
	}
}