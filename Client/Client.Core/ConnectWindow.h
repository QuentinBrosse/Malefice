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
public:
	ConnectWindow(GraphicUtil &gu);
	~ConnectWindow() = default;
	void display();
	void hide();
	bool onCloseButtonClicked(const CEGUI::EventArgs& e);
	bool onConnectButtonClicked(const CEGUI::EventArgs& e);
	std::string getIPEditBox();
	std::string getPortEditBox();
	std::string getNickNameEditBox();
	std::string getPasswordEditBox();

private:
	CEGUI::Window* m_windows;
	CEGUI::Window* m_connectionStatus;
	CEGUI::Editbox* m_ip;
	CEGUI::Editbox* m_port;
	CEGUI::Editbox* m_pseudo;
	CEGUI::Editbox* m_password;
	CEGUI::System& m_systemd;
	CEGUI::FrameWindow* m_frameWindows;
	std::string m_ipStr;
	std::string m_portStr;
	std::string m_pseudoStr;
	GraphicUtil& m_graphicUtils;
};