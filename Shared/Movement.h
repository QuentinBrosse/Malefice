#pragma once

#include "Position.h"

namespace ecs
{
	class Movement : public AComponent
	{
	public:
		Movement() = default;
		Movement(const Position& position);
		~Movement() = default;
	
		void			setDestination(const Position& newDestination);
		const Position&	getDestination() const;

		void			move(Position& startPosition) const;

		void			dump() const;
	private:
		Position	m_destination;
	};
}