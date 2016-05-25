#include "Life.h"

namespace ecs
{
	Life::Life(): AComponent("Life", ComponentType::LIFE),
		m_currentLife(0), m_maxLife(0)
	{

	}

	Life::Life(const Life& cpy) : AComponent("Life", ComponentType::LIFE),
		m_currentLife(cpy.m_currentLife), m_maxLife(cpy.m_maxLife)
	{
	
	}

	Life::Life(ecs::AComponent::ComponentType lifeType) : AComponent("Life", lifeType),
		m_currentLife(0), m_maxLife(0)
	{
	}

	Life::Life(const int maxLife, const ecs::AComponent::ComponentType type) : AComponent("Life", type),
		m_currentLife(maxLife), m_maxLife(maxLife)
	{
	}


	void	Life::init(const int maxLife)
	{
		m_maxLife = maxLife;
		m_currentLife = m_maxLife;
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
	}

	int	 Life::takeDamage(int damage)
	{
		if (damage < 0)
		{
			// Heal ? Or throw exception ?
		}
		int	rest = damage - m_currentLife;
		m_currentLife -= damage;
		if (m_currentLife - damage <= 0)
			m_currentLife = 0;
		return (rest);
	}

	void Life::restore(int quantity)
	{
		m_currentLife += quantity;
		if (m_currentLife > m_maxLife)
			m_currentLife = m_maxLife;
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

	AComponent& Life::affect(const AComponent& rhs)
	{
		const Life&	life = dynamic_cast<const Life&>(rhs);

		m_currentLife = life.m_currentLife;
		m_maxLife = life.m_maxLife;
		return *this;
	}

	AComponent*	Life::createCopy(const AComponent* rhs) const
	{
		const Life* life = dynamic_cast<const Life*>(rhs);
		return new Life(*life);
	}
}
