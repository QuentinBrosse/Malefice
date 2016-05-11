#pragma once

#include <irrlicht.h>
#include <queue>

#include "AComponent.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT GameEventReceiver : public irr::IEventReceiver, public AComponent
	{
	public:

		enum GameEventType
		{
			NOTHING,
			LEFT_ATTACK,
			RIGHT_ATTACK,
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

		GameEventType				getEvent();
		std::queue<GameEventType>	getEvents()	const;

	private:
		std::queue<GameEventType>	m_events;
	};
}