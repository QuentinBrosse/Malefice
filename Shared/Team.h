#pragma once

#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Team : public AComponent
	{
	public:
		const int TEAM_NUMBER;

		Team(int teamNumber);
		~Team();

		int getKill()	const;
		int getDeath()	const;

		void setKill(int);
		void setDeath(int);
		void addDeath();
		void addKill();


		virtual void	dump(std::ostream& os)	const;

		
	private:
		int	m_kill;
		int	m_death;
	};
}
