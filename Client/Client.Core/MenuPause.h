#pragma once

#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include <iostream>

class GraphicUtil;

class MenuPause
{
public:
	MenuPause(GraphicUtil &utilities);
	~MenuPause() = default;
	void display();
	void hide();
	bool onOptionButtonClicked();
	bool onQuitButtonClicked();
	bool onContinueButtonClicked();
	void checkPause();
	bool getEnableStatus();
private:
	GraphicUtil&	m_utilities;
	CEGUI::System&	m_systemd = CEGUI::System::getSingleton();
	CEGUI::Window*	m_windows;
	bool			m_isEnable = true;
};