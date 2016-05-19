#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Team : public AComponent
	{
	public:
		Team();
		Team(const int teamNumber);
		~Team();

		void	init(const int teamNumber);

		int					getKill()	const;
		int					getDeath()	const;

		void				setKill(int);
		void				setDeath(int);
		void				addDeath();
		void				addKill();

		virtual void		dump(std::ostream& os)	const;

		virtual AComponent&	affect(const AComponent& rhs);

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);
	
	private:
		int	m_teamNumber;
		int	m_kill;
		int	m_death;
	};
}
