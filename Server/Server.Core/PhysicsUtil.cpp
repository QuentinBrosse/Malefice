#include "PhysicsUtil.h"
#include "Logger.h"

PhysicsUtil::PhysicsUtil() :
	m_device(nullptr), m_sceneManager(nullptr), m_videoDriver(nullptr)
{
	m_device = irr::createDevice(irr::video::EDT_NULL);
	if (m_device == nullptr)
	{
		LOG_CRITICAL(GENERAL) << "Could not create NULL device.";
	}
	m_videoDriver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_sceneManager->getParameters()->setAttribute(irr::scene::OBJ_TEXTURE_PATH, "media/");

}


irr::IrrlichtDevice*	PhysicsUtil::getDevice() const
{
	return m_device;
}

irr::scene::ISceneManager*	PhysicsUtil::getSceneManager() const
{
	return m_sceneManager;
}

irr::video::IVideoDriver*	PhysicsUtil::getVideoDriver() const
{
	return m_videoDriver;
}
