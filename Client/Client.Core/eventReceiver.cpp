#include "EventReceiver.h"

EventReceiver::EventReceiver()
{
	for (EventReceiver::keyStatesENUM& e : m_keyState)
	{
		e = UP;
	}
}

bool EventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			m_state.leftButtonDown = true;
			break;

		case irr::EMIE_LMOUSE_LEFT_UP:
			m_state.leftButtonDown = false;
			break;

		case irr::EMIE_MOUSE_MOVED:
			m_state.position.X = event.MouseInput.X;
			m_state.position.Y = event.MouseInput.Y;
			break;
		default:
			// Mouse Wheel here (perhaps...)
			break;
		}
	}
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT&& event.JoystickEvent.Joystick == 0)
		m_joystickState = event.JoystickEvent;
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.PressedDown == true)
		{
			m_keyState[event.KeyInput.Key] = DOWN;
		}
		else
		{
			m_keyState[event.KeyInput.Key] = UP;
		}
	}
	return false;
}

const irr::SEvent::SJoystickEvent& EventReceiver::getJoystickState() const
{
	return m_joystickState;
}

const EventReceiver::MouseState& EventReceiver::getMouseState() const
{
	return m_state;
}

EventReceiver::keyStatesENUM EventReceiver::getKeyState(irr::EKEY_CODE keyCode)
{
	return m_keyState[keyCode];
}