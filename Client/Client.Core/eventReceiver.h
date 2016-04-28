#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>
#include <iostream>

class eventReceiver : public irr::IEventReceiver
{
public:
	class MouseState
	{
	public:
		irr::core::position2di position;
		bool leftButtonDown;
		MouseState() : leftButtonDown(false) {};
	};

public:
	virtual bool OnEvent(const irr::SEvent& event); //Irrlicht callback norme exception here
	const irr::SEvent::SJoystickEvent & getJoystickState(void) const;
	const MouseState &getMouseState(void) const;
	eventReceiver() = default;

private:
	irr::SEvent::SJoystickEvent joystickState;
	MouseState m_state;
};