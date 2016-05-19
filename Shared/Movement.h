#pragma once

#include <BitStream.h>
#include "Position.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Movement : public AComponent
	{
	public:
		Movement();
		Movement(const Position& position);
		~Movement() = default;

		virtual void	init(const Position& position);
	
		void			setDestination(const Position& newDestination);
		const Position&	getDestination() const;

		void			move(Position& startPosition) const;


		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

		virtual	AComponent&	affect(const AComponent& rhs);

	private:
		Position	m_destination;
	};
}
