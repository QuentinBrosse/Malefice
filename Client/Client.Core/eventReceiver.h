#pragma once

#include <iostream>
#include <irrlicht.h>

class EventReceiver : public irr::IEventReceiver
{
public:
	class MouseState
	{
	public:
		irr::core::position2di position;
		bool leftButtonDown;
		MouseState() : leftButtonDown(false) {};
	};
	enum keyStatesENUM {UP, DOWN};

public:
	virtual bool OnEvent(const irr::SEvent& event); //Irrlicht callback norme exception here
	const irr::SEvent::SJoystickEvent& getJoystickState(void) const;
	const MouseState& getMouseState(void) const;
	EventReceiver::keyStatesENUM getKeyState(irr::EKEY_CODE keyCode);
	EventReceiver();
	EventReceiver::keyStatesENUM* getKeyStateList();
private:
	irr::SEvent::SJoystickEvent m_joystickState;
	MouseState m_state;
	keyStatesENUM m_keyState[irr::KEY_KEY_CODES_COUNT];
};