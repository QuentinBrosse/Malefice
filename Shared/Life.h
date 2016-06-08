#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Life : public AComponent
	{
	public:
		Life();
		Life(const Life& cpy);
		Life(ecs::AComponent::ComponentType lifeType);
		Life(const int maxLife, const ecs::AComponent::ComponentType type);
		~Life() = default;

		virtual void	init(const int maxLife);

		int		get() const;
		void	set(int life);
		int		takeDamage(int damage);
		void	restore(int quantity);

		virtual	void		dump(std::ostream& os)	const;
			
		virtual void		serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void		deserialize(RakNet::BitStream& in);

		virtual AComponent&	affect(const AComponent& rhs);
		virtual AComponent*	createCopy(const AComponent* rhs) const;

		int					getMaxLife() const;
	protected:
		int	m_currentLife;		
		int	m_maxLife;
	};
}
