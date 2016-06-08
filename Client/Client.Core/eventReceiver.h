#pragma once

#include <iostream>
#include <irrlicht.h>
#include <CEGUI\CEGUI.h>
#include <queue>

class EventReceiver : public irr::IEventReceiver
{
public:

	enum GameEventType
	{
		NOTHING,
		LEFT_ATTACK,
		NEXT_WEAPON,
		PREC_WEAPON,
		CHANGE_MANAGER,
		ZOOM,
		RELOAD,
		GAME_EVENT_TYPE_COUNT,
	};

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
	static unsigned char EventReceiver::irrlichtKeyToCEGUIKey(irr::EKEY_CODE kc);

	std::queue<GameEventType>	getEvents()	const;
	GameEventType				getEvent();

private:
	irr::SEvent::SJoystickEvent m_joystickState;
	MouseState m_state;
	keyStatesENUM m_keyState[irr::KEY_KEY_CODES_COUNT];
	std::queue<GameEventType>	m_events;
	
};