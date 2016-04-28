#include "eventReceiver.h"

bool eventReceiver::OnEvent(const irr::SEvent& event)
{
	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			m_state.LeftButtonDown = true;
			break;

		case irr::EMIE_LMOUSE_LEFT_UP:
			m_state.LeftButtonDown = false;
			break;

		case irr::EMIE_MOUSE_MOVED:
			m_state.Position.X = event.MouseInput.X;
			m_state.Position.Y = event.MouseInput.Y;
			break;
		default:
			// Mouse Wheel here (perhaps...)
			break;
		}
	}
	if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && event.JoystickEvent.Joystick == 0)
		JoystickState = event.JoystickEvent;
	return false;
}

const irr::SEvent::SJoystickEvent &eventReceiver::GetJoystickState(void) const
{
	return JoystickState;
}

const eventReceiver::MouseState &eventReceiver::GetMouseState(void) const
{
	return m_state;
}