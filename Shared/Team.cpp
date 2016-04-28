#include "Team.h"

namespace ecs
{
	Team::Team(int team) : AComponent("Team", COMPONENT_TEAM), 
		TEAM(team), m_iDeath(0), m_iKill(0)
	{

	}

	Team::~Team()
	{

	}

	void Team::dump() const
	{
		std::cout << "[Team : " << TEAM << "]" << std::endl;
		std::cout << "[Kill : " << m_iKill << "]" << std::endl;
		std::cout << "[Death : " << m_iDeath << "]" << std::endl;
	}

	int Team::getDeath() const
	{
		return (m_iDeath);
	}

	int Team::getKill() const
	{
		return (m_iKill);
	}

	void Team::setDeath(int death)
	{
		m_iDeath = death;
	}

	void Team::setKill(int kill)
	{
		m_iKill = kill;
	}

	void Team::addDeath()
	{
		m_iDeath += 1;
	}

	void Team::addKill()
	{
		m_iKill += 1;
	}
}