#include <iostream>
#include "Team.h"

namespace ecs
{
	Team::Team() : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_team(ecs::Team::TeamType::TEAM_COUNT), m_kill(0), m_death(0)
	{
	}

	Team::Team(const Team & cpy) : AComponent("team", ecs::AComponent::ComponentType::TEAM),
		m_death(cpy.m_death), m_kill(cpy.m_kill), m_team(cpy.m_team)
	{
	}

	Team::Team(ecs::Team::TeamType team) : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_team(team), m_death(0), m_kill(0)
	{

	}

	Team::~Team()
	{
	}

	
	void	Team::init(ecs::Team::TeamType team)
	{
		m_team = team;
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
		os << "Team {team = " << static_cast<int>(m_team) << ", kill = " << m_kill << ", death = " << m_death << "}";
	}

	AComponent & Team::affect(const AComponent & rhs)
	{
		const Team&	team = dynamic_cast<const Team&>(rhs);

		m_death = team.m_death;
		m_kill = team.m_kill;
		m_team = team.m_team;

		return *this;
	}


	void	Team::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_team);
		out.Write(m_kill);
		out.Write(m_death);
	}

	void	Team::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_team);
		in.Read(m_kill);
		in.Read(m_death);
	}

	AComponent * Team::createCopy(const AComponent * rhs) const
	{
		const Team* team = dynamic_cast<const Team*>(rhs);

		return new Team(*team);
	}
}
