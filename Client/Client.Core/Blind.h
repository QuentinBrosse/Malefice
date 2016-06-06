#pragma once

#include <string>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <chrono>
#include <iostream>

class Blind
{
public:
	Blind();
	~Blind() = default;
	void display();
	void hide();
	void refresh();
private:
	unsigned int	m_alpha;
	std::chrono::milliseconds	m_delay;
	const int		m_maxAplha;
	CEGUI::Window*	m_windows;
	CEGUI::System&	m_systemd;
	std::chrono::milliseconds m_time;
	const int		m_step;
	bool			m_isDisplayed;
};