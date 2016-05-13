#pragma once

#include <string>
#include <iostream>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include "NetworkModule.h"
#include "waitingRoom.h"

class GraphicUtil;

class ConnectWindow
{
private:
	CEGUI::Window* m_windows;
	CEGUI::Editbox* m_ip;
	CEGUI::Editbox* m_port;
	CEGUI::System& m_systemd = CEGUI::System::getSingleton();
	CEGUI::FrameWindow* m_frameWindows;
	std::string m_ipStr;
	std::string m_portStr;
	GraphicUtil& m_graphicUtils;
public:
	ConnectWindow(GraphicUtil &gu);
	~ConnectWindow() = default;
	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	bool onConnectButtonClicked(const CEGUI::EventArgs& e);
	std::string getIPEditBox();
	std::string getPortEditBox();
};