#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Team : public AComponent
	{
	public:
		enum class TeamType : int
		{
			Team1,
			Team2,
			Predator,
			TEAM_COUNT
		};

		Team();
		Team(const Team& cpy);
		Team(ecs::Team::TeamType team);
		~Team();

		void	init(ecs::Team::TeamType team);

		int					getKills()	const;
		int					getDeaths()	const;

		void				setKills(int);
		void				setDeaths(int);
		void				addDeath();
		void				addKill();
		const TeamType		getTeam() const;

		virtual void		dump(std::ostream& os)	const;

		virtual AComponent&	affect(const AComponent& rhs);

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);
	
		virtual  AComponent*	createCopy(const AComponent* rhs) const;

	private:
		ecs::Team::TeamType	m_team;
		int	m_kills;
		int	m_deaths;
	};
}
