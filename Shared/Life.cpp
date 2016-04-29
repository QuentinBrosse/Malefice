#include "Life.h"

namespace ecs
{
	Life::Life(int iMaxLife) : AComponent("Life", LIFE),
		m_iCurrentLife(iMaxLife), MAX_LIFE(iMaxLife)
	{

	}

	int Life::get() const
	{
		return m_iCurrentLife;
	}

	void Life::set(int iLife)
	{
		if (iLife < 0)
		{
			// Error can't have negative life.
		}
		if (iLife > MAX_LIFE)
		{
			// Set to max Life ? Or throw exception ?
		}
		m_iCurrentLife = iLife;
		if (m_iCurrentLife == 0)
		{
			onDeath();
		}
	}

	void Life::takeDamage(int iDamage)
	{
		if (iDamage < 0)
		{
			// Heal ? Or throw exception ?
		}
		m_iCurrentLife -= iDamage;
		if (m_iCurrentLife <= 0)
		{
			m_iCurrentLife = 0;
			onDeath();
		}
	}

	void Life::restore(int iQuantity)
	{
		m_iCurrentLife += iQuantity;
		if (m_iCurrentLife > MAX_LIFE)
			m_iCurrentLife = MAX_LIFE;
	}

	void Life::onDeath()
	{
		// Death behavior ...
	}

	void Life::dump() const
	{
		std::cout << "[Life " << m_iCurrentLife << "/" << MAX_LIFE<< "]" << std::endl;
	}
}