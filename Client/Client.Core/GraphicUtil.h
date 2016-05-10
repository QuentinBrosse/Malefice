#pragma once

#include <Singleton.h>
#include "Camera.h"
#include "EventReceiver.h"
#include "MainMenu.h"
#include "NetworkModule.h"

class GraphicUtil
{
public:
	GraphicUtil(const irr::video::E_DRIVER_TYPE& driverType, const irr::core::dimension2d<irr::u32>& windowSize, const ecs::Position& startPostion, NetworkModule& networkModule);
	~GraphicUtil();

	void	initGraphics();
	irr::IrrlichtDevice* getDevice();
	irr::scene::ISceneManager* getSceneManager();
	Camera* getCamera();
	EventReceiver& getCEGUIEventReceiver();
	void CEGUIEventInjector();
	MainMenu* getMainMenu();
	irr::video::IVideoDriver* getDriver();
	void setGuiCamera();
	void setFPSCamera(float moveSpeed = 1.f, float rotationSpeed = 0.06f);
private:
	NetworkModule&				m_networkModule;
	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_camera;
	Camera*						m_guiCamera;
	EventReceiver				m_receiver;
	irr::SKeyMap*				m_keyMap;
	MainMenu*					m_menu;
};