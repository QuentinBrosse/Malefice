#pragma once

#include <Singleton.h>
#include "Camera.h"

class GraphicUtil
{
public:
	GraphicUtil(const irr::video::E_DRIVER_TYPE& driverType, const irr::core::dimension2d<irr::u32>& windowSize, const ecs::Position& startPostion);
	~GraphicUtil();

	void	initGraphics();
private:

	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_camera;
};