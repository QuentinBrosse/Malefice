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
#include "MasterList.h"
#include "Blind.h"
#include "TouchedFx.h"
#include "YourDead.h"
#include "scoreTab.h"

class GraphicUtil : public Singleton<GraphicUtil>
{
	friend class Singleton<GraphicUtil>;
protected:
	GraphicUtil();
	~GraphicUtil();

public:
	void						initGraphics();
	irr::IrrlichtDevice*		getDevice();
	irr::scene::ISceneManager*	getSceneManager();
	Camera*						getFPSCamera();
	EventReceiver&				getCEGUIEventReceiver();
	void						CEGUIEventInjector();
	MainMenu*					getMainMenu();
	irr::video::IVideoDriver*	getDriver();
	void						setGuiCamera();
	MenuPause*					getMenuPause();
	void						setFPSCamera();
	MenuOptions*				getMenuOptions();
	ConnectWindow*				getConnectWindow();
	WaitingRoom*				getWaitingRoom();
	InGameGUI*					getHUD();
	Blind*						getBlindFx();
	TouchedFx*					getTouchedFx();
	MasterList*					getMasterList();
	YourDead*					getDeadGUI();
	scoreTab*					getScoreTab();
	bool						isInFPSMode()		const;

private:
	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_FPSCamera;
	Camera*						m_guiCamera;
	EventReceiver				m_receiver;
	irr::SKeyMap*				m_keyMap;
	MainMenu*					m_menu;
	MenuPause*					m_menuPause;
	MenuOptions*				m_menuOptions;
	ConnectWindow*				m_connectWindow;
	WaitingRoom*				m_salon;
	InGameGUI*					m_hud;
	MasterList*					m_masterList;
	Blind*						m_blindFx;
	TouchedFx*					m_touchedFx;
	YourDead*					m_deadGUI;
	scoreTab*					m_scoreTab;
	bool						m_isInFPSMode;
};