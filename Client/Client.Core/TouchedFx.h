#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <iostream>
#include <chrono>

class TouchedFx
{
public:
	TouchedFx();
	~TouchedFx() = default;
	void display();
	void hide();
	void refresh();
private:
	CEGUI::Window*				m_windows;
	CEGUI::System&				m_systemd;
	bool						m_isDisplayed;
	std::chrono::milliseconds	m_time;
	std::chrono::milliseconds	m_delay;
};