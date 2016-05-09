#pragma once

#include <string>
#include <iostream>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>

class ConnectWindow
{
private:
	CEGUI::Window* m_windows;
	CEGUI::System& m_systemd = CEGUI::System::getSingleton();
	CEGUI::FrameWindow* m_frameWindows;
public:
	ConnectWindow();
	~ConnectWindow() = default;
	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
};