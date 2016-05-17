#pragma once

#include <iostream>
#include <irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/System.h>
#include "ConnectWindow.h"
#include "NetworkModule.h"

class GraphicUtil;

class MainMenu
{
public:
	MainMenu(GraphicUtil &gu);
	~MainMenu() = default;
	
	void display();
	void hide();
	bool onPlayButtonClicked(const CEGUI::EventArgs& e);
	bool onOptionButtonClicked(const CEGUI::EventArgs& e);
	bool onQuitButtonClicked(const CEGUI::EventArgs& e);

private:
	CEGUI::Window *m_windows;
	CEGUI::System &m_systemd;
	irr::SKeyMap *m_keyMap;
	irr::IrrlichtDevice *m_device;
	irr::video::IVideoDriver *m_driver;
	irr::scene::ISceneManager *m_sceneManager;
	GraphicUtil &m_graphicUtils;
};
