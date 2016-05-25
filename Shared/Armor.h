#pragma once

#include <BitStream.h>
#include "Life.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Armor: public Life
	{
	public:
		Armor();
		Armor(int maxHP);
		~Armor()	= default;

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

		virtual AComponent&	affect(const AComponent& rhs);
		virtual AComponent*	createCopy(const AComponent* rhs) const;
	};
}
