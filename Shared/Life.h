#pragma once

#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Life : public AComponent
	{
	public:
		const int MAX_LIFE;

		Life(const int maxLife, const ComponentType type);
		~Life() = default;

		int		get() const;
		void	set(int life);
		void	takeDamage(int damage);
		void	restore(int quantity);

		virtual void onDeath();
		// why virtual ?-> 
		//
		// Maybe behavior while be different according
		// to players, predator and maybe destructible object.
		//
		// We may implemente (with same NAME and TYPE)
		// different Life object for every
		// death system to simplify game management without take
		// care of Life implementation. 

		virtual void	dump(std::ostream& os)	const;


	protected:
		int	m_currentLife;		
	};
}
