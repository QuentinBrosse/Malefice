#include "Team.h"

namespace ecs
{
	Team::Team(int iTeamNumber) : AComponent("Team", COMPONENT_TEAM), 
		TEAM_NUMBER(iTeamNumber), m_iDeath(0), m_iKill(0)
	{

	}

	Team::~Team()
	{

	}

	void Team::dump() const
	{
		std::cout << "[Team : " << TEAM_NUMBER << "]" << std::endl;
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

	void Team::setDeath(int iDeath)
	{
		m_iDeath = iDeath;
	}

	void Team::setKill(int iKill)
	{
		m_iKill = iKill;
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