#include <iostream>
#include "Life.h"

namespace ecs
{
	Life::Life(ecs::ComponentType lifeType) : AComponent("Life", lifeType)
	{
	}

	Life::Life(const int maxLife, const ComponentType type) : AComponent("Life", type),
		m_currentLife(maxLife), m_maxLife(maxLife)
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
		if (life > m_maxLife)
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
		if (m_currentLife > m_maxLife)
			m_currentLife = m_maxLife;
	}

	void Life::onDeath()
	{
		// Death behavior ...
	}



	void	Life::dump(std::ostream& os)	const
	{
		os << "Life {currentLife = " << m_currentLife << ", maxLife = " << m_maxLife << "}";
	}


	void	Life::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Life::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
