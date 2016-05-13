#pragma once

#include <Singleton.h>
#include "Camera.h"
#include "EventReceiver.h"
#include "MainMenu.h"
#include "MenuPause.h"
#include "NetworkModule.h"
#include "MenuOptions.h"
#include "ConnectWindow.h"
#include "WaitingRoom.h"
#include "InGameGUI.h"

class GraphicUtil : public Singleton<GraphicUtil>
{
	friend class Singleton<GraphicUtil>;
protected:
	GraphicUtil();
	~GraphicUtil();

public:
	void	initGraphics();
	irr::IrrlichtDevice* getDevice();
	irr::scene::ISceneManager* getSceneManager();
	Camera* getFPSCamera();
	EventReceiver& getCEGUIEventReceiver();
	void CEGUIEventInjector();
	MainMenu* getMainMenu();
	irr::video::IVideoDriver* getDriver();
	void setGuiCamera();
	MenuPause* getMenuPause();
	void setFPSCamera();
	MenuOptions* getMenuOptions();
	ConnectWindow* getConnectWindow();
	WaitingRoom* getWaitingRoom();
	InGameGUI* getHUD();
private:
	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_FPSCamera;
	Camera*						m_guiCamera;
	EventReceiver				m_receiver;
	irr::SKeyMap*				m_keyMap;
	MainMenu*					m_menu = nullptr;
	MenuPause*					m_menuPause = nullptr;
	MenuOptions*				m_menuOptions = nullptr;
	ConnectWindow*				m_connectWindow = nullptr;
	WaitingRoom*				m_salon = nullptr;
	InGameGUI*					m_hud = nullptr;
};