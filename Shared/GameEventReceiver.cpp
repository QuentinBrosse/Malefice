#include "GameEventReceiver.h"

namespace ecs
{

	GameEventReceiver::GameEventReceiver(): AComponent("GameEventReceiver", GAME_EVENT_RECEIVER)
	{
		
	}

	bool GameEventReceiver::OnEvent(const irr::SEvent& event)
	{
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch (event.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				m_events.push(GameEventReceiver::GameEventType::LEFT_ATTACK);
				break;

			case irr::EMIE_RMOUSE_PRESSED_DOWN:
				m_events.push(GameEventReceiver::GameEventType::RIGHT_ATTACK);
				break;

			case irr::EMIE_MMOUSE_PRESSED_DOWN:
				m_events.push(GameEventReceiver::GameEventType::ZOOM);
				break;

			case irr::EMIE_MOUSE_WHEEL:
				if (event.MouseInput.Wheel < 0)
					m_events.push(GameEventReceiver::GameEventType::PREC_WEAPON);
				else
					m_events.push(GameEventReceiver::GameEventType::NEXT_WEAPON);
				break;

			default:
				break;
			}
		}
		else if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		{
			switch (event.KeyInput.Key)
			{

			case irr::KEY_KEY_1:
				m_events.push(GameEventReceiver::GameEventType::PREC_SPELL);
				break;

			case irr::KEY_KEY_2:
				m_events.push(GameEventReceiver::GameEventType::NEXT_SPELL);
				break;

			default:
				break;
			}
		}
		return false;
	}

	GameEventReceiver::GameEventType		GameEventReceiver::getEvent()
	{
		GameEventReceiver::GameEventType	event;

		event = m_events.front();
		m_events.pop();
		return (event);
	}

	std::queue<GameEventReceiver::GameEventType> GameEventReceiver::getEvents() const
	{
		return m_events;
	}

};
