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
	
		void			setDestination(const Position& newDestination);
		const Position&	getDestination() const;

		void			move(Position& startPosition) const;


		void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		Position	m_destination;
	};
}
