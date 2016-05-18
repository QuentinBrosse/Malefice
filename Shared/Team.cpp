#include <iostream>
#include "Team.h"

namespace ecs
{
	Team::Team() : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_teamNumber(0), m_kill(0), m_death(0)
	{
	}

	Team::Team(const int teamNumber) : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_teamNumber(teamNumber), m_death(0), m_kill(0)
	{

	}

	Team::~Team()
	{
	}

	
	void	Team::init(const int teamNumber)
	{
		m_teamNumber = teamNumber;
		m_death = 0;
		m_kill = 0;
	}


	int Team::getDeath() const
	{
		return (m_death);
	}

	int Team::getKill() const
	{
		return (m_kill);
	}

	void Team::setDeath(int death)
	{
		m_death = death;
	}

	void Team::setKill(int kill)
	{
		m_kill = kill;
	}

	void Team::addDeath()
	{
		m_death += 1;
	}

	void Team::addKill()
	{
		m_kill += 1;
	}


	void	Team::dump(std::ostream& os)	const
	{
		os << "Team {teamNumber = " << m_teamNumber << ", kill = " << m_kill << ", death = " << m_death << "}";
	}


	void	Team::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_teamNumber);
		out.Write(m_kill);
		out.Write(m_death);
	}

	void	Team::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_teamNumber);
		in.Read(m_kill);
		in.Read(m_death);
	}
}
