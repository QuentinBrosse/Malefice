#pragma once

#include <irrlicht.h>
#include <queue>

#include "AComponent.h"

namespace ecs
{
	class GameEventReceiver : public irr::IEventReceiver, public AComponent
	{
	public:

		enum GameEventType
		{
			NOTHING,
			LEFT_CLICK_ATTACK,
			RIGHT_CLICK_ATTACK,
			NEXT_WEAPON,
			PREC_WEAPON,
			NEXT_SPELL,
			PREC_SPELL,
			ZOOM,
			GAME_EVENT_TYPE_COUNT,
		};

		GameEventReceiver();
		~GameEventReceiver() = default;

		virtual bool	OnEvent(const irr::SEvent& event); //Irrlicht callback norme exception here	

		GameEventType	getEvent();

	private:
		std::queue<GameEventType>	m_events;
	};
}