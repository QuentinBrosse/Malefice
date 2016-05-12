#pragma once

#include "Position.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Movement : public AComponent
	{
	public:
		Movement() = default;
		Movement(const Position& position);
		~Movement() = default;
	
		void			setDestination(const Position& newDestination);
		const Position&	getDestination() const;

		void			move(Position& startPosition) const;


		void	dump(std::ostream& os)	const;


	private:
		Position	m_destination;
	};
}
