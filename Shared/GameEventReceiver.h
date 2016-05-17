#pragma once

#include <queue>
#include <irrlicht.h>
#include <BitStream.h>
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
			CHANGE_MANAGER,
			ZOOM,
			GAME_EVENT_TYPE_COUNT,
		};

		GameEventReceiver();
		~GameEventReceiver()	= default;

		virtual bool	OnEvent(const irr::SEvent& event); //Irrlicht callback norme exception here	

		GameEventType				getEvent();
		std::queue<GameEventType>	getEvents()	const;


		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		std::queue<GameEventType>	m_events;
	};
}
