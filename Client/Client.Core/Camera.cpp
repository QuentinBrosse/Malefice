#include <iostream>
#include "Camera.h"
#include "MathUtility.h"

Camera::Camera(const ecs::Position& position, irr::scene::ISceneManager* sceneManager) :
	m_camera(nullptr)
{
	loadKey(position, sceneManager, true);
}

Camera::~Camera()
{
//	if (m_camera)
	//	m_camera->remove();
}

ecs::Position Camera::getPosition() const
{
	return ecs::Position(m_camera->getPosition(), m_camera->getRotation());
}

ecs::Position Camera::getPositionTarget() const
{
	return ecs::Position(m_camera->getPosition(), m_camera->getTarget());
}

irr::core::vector3df Camera::getTarget() const
{
	return m_camera->getTarget();
}

void Camera::init()
{
	m_camera->setFOV(utility::MathUtility::degreesToRadians(90.f));
	m_camera->setNearValue(0.8f);
}

void Camera::loadKey(const ecs::Position& position, irr::scene::ISceneManager* sceneManager, bool normalKey)
{
	// DEBUG
	//if (m_camera)
		//m_camera->remove();
	irr::SKeyMap	keyMap[5];
	if (normalKey)
	{
		keyMap[0].Action = irr::EKA_MOVE_FORWARD;
		keyMap[0].KeyCode = irr::KEY_KEY_Z;

		keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
		keyMap[1].KeyCode = irr::KEY_KEY_S;

		keyMap[2].Action = irr::EKA_STRAFE_LEFT;
		keyMap[2].KeyCode = irr::KEY_KEY_Q;

		keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
		keyMap[3].KeyCode = irr::KEY_KEY_D;

		keyMap[4].Action = irr::EKA_JUMP_UP;
		keyMap[4].KeyCode = irr::KEY_SPACE;
	}
	else
	{
		keyMap[0].Action = irr::EKA_MOVE_FORWARD;
		keyMap[0].KeyCode = irr::KEY_KEY_S;

		keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
		keyMap[1].KeyCode = irr::KEY_KEY_Z;

		keyMap[2].Action = irr::EKA_STRAFE_LEFT;
		keyMap[2].KeyCode = irr::KEY_KEY_D;

		keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
		keyMap[3].KeyCode = irr::KEY_KEY_Q;

		keyMap[4].Action = irr::EKA_JUMP_UP;
		keyMap[4].KeyCode = irr::KEY_SPACE;
	}
	m_camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, .3f, nodePickable::NOT_PICKABLE, keyMap, 5, true, 3.f);
	m_camera->setPosition(irr::core::vector3df(position.getVectorPosition()));
	m_camera->setTarget(irr::core::vector3df(position.getVectorRotation()));
	init();
}

void Camera::setPosition(const ecs::Position & newPosition)
{
	m_camera->setPosition(newPosition.getVectorPosition());
	m_camera->setRotation(newPosition.getVectorRotation());
	m_camera->setScale(newPosition.getVectorScale());
}
