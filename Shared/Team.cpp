#include <iostream>
#include "Team.h"

namespace ecs
{
	Team::Team() : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_team(ecs::Team::TeamType::TEAM_COUNT), m_kills(0), m_deaths(0)
	{
	}

	Team::Team(const Team & cpy) : AComponent("team", ecs::AComponent::ComponentType::TEAM),
		m_deaths(cpy.m_deaths), m_kills(cpy.m_kills), m_team(cpy.m_team)
	{
	}

	Team::Team(ecs::Team::TeamType team) : AComponent("Team", ecs::AComponent::ComponentType::TEAM),
		m_team(team), m_deaths(0), m_kills(0)
	{

	}

	Team::~Team()
	{
	}

	
	void	Team::init(ecs::Team::TeamType team)
	{
		m_team = team;
		m_deaths = 0;
		m_kills = 0;
	}


	int Team::getDeaths() const
	{
		return (m_deaths);
	}

	int Team::getKills() const
	{
		return (m_kills);
	}

	void Team::setDeaths(int death)
	{
		m_deaths = death;
	}

	void Team::setKills(int kill)
	{
		m_kills = kill;
	}

	void Team::addDeath()
	{
		m_deaths += 1;
	}

	void Team::addKill()
	{
		m_kills += 1;
	}


	void	Team::dump(std::ostream& os)	const
	{
		os << "Team {team = " << static_cast<int>(m_team) << ", kill = " << m_kills << ", death = " << m_deaths << "}";
	}

	AComponent & Team::affect(const AComponent & rhs)
	{
		const Team&	team = dynamic_cast<const Team&>(rhs);

		m_deaths = team.m_deaths;
		m_kills = team.m_kills;
		m_team = team.m_team;

		return *this;
	}


	void	Team::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_team);
		out.Write(m_kills);
		out.Write(m_deaths);
	}

	void	Team::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_team);
		in.Read(m_kills);
		in.Read(m_deaths);
	}

	AComponent* Team::createCopy(const AComponent * rhs) const
	{
		const Team* team = dynamic_cast<const Team*>(rhs);

		return new Team(*team);
	}

	const Team::TeamType Team::getTeam() const
	{
		return m_team;
	}
}
