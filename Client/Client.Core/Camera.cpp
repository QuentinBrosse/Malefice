#include "Camera.h"

namespace ecs
{
	Camera::Camera(const Position& position, irr::scene::ISceneManager* sceneManager) : AComponent("Camera", CAMERA)
	{
		m_camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);
		m_camera->setPosition(irr::core::vector3df(position.getVectorPosition()));
		m_camera->setTarget(irr::core::vector3df(position.getVectorTarget()));
	}

	Camera::~Camera()
	{
		// delete m_camera?
	}

	Position Camera::getPosition() const
	{
		return Position(m_camera->getPosition().X, m_camera->getPosition().Y, m_camera->getPosition().Z, m_camera->getTarget().X, m_camera->getTarget().Y, m_camera->getTarget().Z);
	}

}