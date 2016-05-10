#pragma once

#include <Singleton.h>
#include "Camera.h"
#include "EventReceiver.h"
#include "MainMenu.h"
#include "NetworkModule.h"

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
	Camera* getCamera();
	EventReceiver& getCEGUIEventReceiver();
	void CEGUIEventInjector();
	MainMenu* getMainMenu();
	irr::video::IVideoDriver* getDriver();
	void setGuiCamera();
	void setFPSCamera(float moveSpeed = 0.06f, float rotationSpeed = 100.0f);
private:
	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_camera;
	Camera*						m_guiCamera;
	EventReceiver				m_receiver;
	irr::SKeyMap*				m_keyMap;
	MainMenu*					m_menu;
};