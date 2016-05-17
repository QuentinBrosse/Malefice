#include <iostream>
#include "Life.h"

namespace ecs
{
	Life::Life(ecs::AComponent::ComponentType lifeType) : AComponent("Life", lifeType),
		m_currentLife(0), m_maxLife(0)
	{
	}

	Life::Life(const int maxLife, const ecs::AComponent::ComponentType type) : AComponent("Life", type),
		m_currentLife(maxLife), m_maxLife(maxLife)
	{
	}


	void	Life::init()
	{
		// TODO: implement constructor logic here
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


	void	Life::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_currentLife);
		out.Write(m_maxLife);
	}

	void	Life::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_currentLife);
		in.Read(m_maxLife);
	}
}
