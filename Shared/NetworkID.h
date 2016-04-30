#pragma once

#include "AComponent.h"

namespace ecs
{
	class NetworkID : public AComponent
	{
	public:
		const unsigned int	ID;

		NetworkID(unsigned int id);
		~NetworkID()	= default;

		void dump()	const;

		void setCurrentPlayer(bool value);
		bool isCurrentPlayer()	const;


	private:
		bool m_isCurrentPlayer;
	};

}
