#include "GraphicUtil.h"

GraphicUtil::GraphicUtil(const irr::video::E_DRIVER_TYPE& driverType, const irr::core::dimension2d<irr::u32>& windowSize, const ecs::Position& startPosition)
{
	m_device = irr::createDevice(driverType, windowSize, 16, false);
	if (!m_device)
	{
		// TODO: Throw exception
		std::cout << "Cannot create Device !" << std::endl;
	}
	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_camera = new Camera(startPosition, m_sceneManager);
}

GraphicUtil::~GraphicUtil()
{
	if(m_camera)
		delete (m_camera);
	// Delete all?
}

void GraphicUtil::initGraphics()
{
	m_device->getCursorControl()->setVisible(false);
	m_sceneManager->getParameters()->setAttribute(irr::scene::OBJ_TEXTURE_PATH, "media/"); //TODO: Define Texture's Path
	m_camera->init();
}

