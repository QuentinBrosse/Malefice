#pragma once

#include <Singleton.h>
#include "Camera.h"

class GraphicUtil : public Singleton<GraphicUtil>
{
	friend class Singleton<GraphicUtil>;

public:

protected:
	GraphicUtil(const irr::video::E_DRIVER_TYPE& driverType, const irr::core::dimension2d<irr::u32>& windowSize, const ecs::Position& startPostion);
	~GraphicUtil();

private:
	void	initGraphics();

	irr::IrrlichtDevice*		m_device;
	irr::scene::ISceneManager*	m_sceneManager;
	irr::video::IVideoDriver*	m_driver;
	Camera*						m_camera;
};