#pragma once

#include "AComponent.h"

namespace ecs
{
	class NetworkID: public AComponent
	{
	public:
		NetworkID(networkID id);
		~NetworkID() = default;

		void dump() const;

		void setCurrentPlayer(bool value);
		bool isCurrentPlayer() const;

	public:
		const networkID ID;
	private:
		bool m_isCurrentPlayer;
	};

}