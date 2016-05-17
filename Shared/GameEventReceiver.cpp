#include "GameEventReceiver.h"
#include <iostream>
#include <boost\serialization\queue.hpp>

namespace ecs
{
	GameEventReceiver::GameEventReceiver(): AComponent("GameEventReceiver", ecs::AComponent::ComponentType::GAME_EVENT_RECEIVER),
		m_events()
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
				m_events.push(GameEventReceiver::GameEventType::CHANGE_MANAGER);
				break;

			case irr::KEY_KEY_2:
				m_events.push(GameEventReceiver::GameEventType::CHANGE_MANAGER);
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


	void	GameEventReceiver::dump(std::ostream& os)	const
	{
		os << "GameEventReceiver {events.size = " << m_events.size();
		if (m_events.size() > 0)
		{
			os << ", events.front = " << m_events.front() << ", events.back = " << m_events.back();
		}
		os << "}";
	}


	void	GameEventReceiver::serialize(RakNet::BitStream& out)	const
	{
		// Won't be sent over network (will be modified with RPCs)
	}

	void	GameEventReceiver::deserialize(RakNet::BitStream& in)
	{
		// Won't be sent over network (will be modified with RPCs)
	}
};
