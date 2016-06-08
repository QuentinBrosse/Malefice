#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <chrono>
#include <iostream>

class YourDead
{
public:
	YourDead();
	~YourDead() = default;
	void hide();
	void display();
	void setPseudo(const std::string &);
	void refresh();
private:
	CEGUI::Window*				m_windows;
	CEGUI::System&				m_systemd;
	bool						m_isDisplayed;
	std::chrono::milliseconds	m_time;
	std::chrono::milliseconds	m_delay;
};