#pragma once

#include "AComponent.h"

namespace ecs
{
	class Life: public AComponent
	{
	public:
		Life(int maxLife);
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

		void dump() const;

	private:
		int m_currentLife;
	public:
		const int MAX_LIFE;
	};

}