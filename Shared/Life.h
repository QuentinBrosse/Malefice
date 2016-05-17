#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Life : public AComponent
	{
	public:
		Life(ecs::AComponent::ComponentType lifeType);
		Life(const int maxLife, const ecs::AComponent::ComponentType type);
		~Life() = default;

		virtual void	init();

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

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	protected:
		int	m_currentLife;		
		int	m_maxLife;
	};
}
