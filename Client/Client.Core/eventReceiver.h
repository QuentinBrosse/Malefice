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
		irr::core::position2di Position;
		bool LeftButtonDown;
		MouseState() : LeftButtonDown(false) {};
	};

public:
	virtual bool OnEvent(const irr::SEvent& event); //Irrlicht callback
	const irr::SEvent::SJoystickEvent & GetJoystickState(void) const;
	const MouseState &GetMouseState(void) const;
	eventReceiver() = default;

private:
	irr::SEvent::SJoystickEvent JoystickState;
	MouseState m_state;
};