#include <iostream>
#include "Team.h"

namespace ecs
{
	Team::Team() : AComponent("Team", ecs::ComponentType::TEAM)
	{
	}

	Team::Team(int teamNumber) : AComponent("Team", TEAM), 
		m_teamNumber(teamNumber), m_death(0), m_kill(0)
	{

	}

	Team::~Team()
	{

	}

	void	Team::dump(std::ostream& os)	const
	{
		os << "[Team : " << m_teamNumber << "]" << std::endl;
		os << "[Kill : " << m_kill << "]" << std::endl;
		os << "[Death : " << m_death << "]" << std::endl;
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


	void	Team::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Team::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
}
