#include "Team.h"

namespace ecs
{
	Team::Team(int teamNumber) : AComponent("Team", COMPONENT_TEAM), 
		TEAM_NUMBER(teamNumber), m_death(0), m_kill(0)
	{

	}

	Team::~Team()
	{

	}

	void Team::dump() const
	{
		std::cout << "[Team : " << TEAM_NUMBER << "]" << std::endl;
		std::cout << "[Kill : " << m_kill << "]" << std::endl;
		std::cout << "[Death : " << m_death << "]" << std::endl;
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
}