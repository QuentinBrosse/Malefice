#include <iostream>
#include "Camera.h"
#include "MathUtility.h"

Camera::Camera(const ecs::Position& position, irr::scene::ISceneManager* sceneManager) :
	m_camera(nullptr), m_cameraAnimator(nullptr)
{
	init(position, sceneManager);
}

Camera::~Camera()
{
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

irr::scene::ICameraSceneNode * Camera::getNode() const
{
	return m_camera;
}

void Camera::init(const ecs::Position& position, irr::scene::ISceneManager* sceneManager)
{
	m_camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, .3f, nodePickable::NOT_PICKABLE, nullptr, 0, true, 3.f); 
	m_cameraAnimator = (irr::scene::ISceneNodeAnimatorCameraFPS*)* m_camera->getAnimators().begin();
	loadDefaultKeys();
	m_camera->setPosition(irr::core::vector3df(position.getVectorPosition()));
	m_camera->setTarget(irr::core::vector3df(position.getVectorRotation()));
	m_camera->setFOV(utility::MathUtility::degreesToRadians(90.f));
	m_camera->setNearValue(0.8f);
}

void Camera::loadInvertKeys()
{
	irr::SKeyMap	keyMap[5];

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

	m_cameraAnimator->setKeyMap(keyMap, 5);
}

void	Camera::loadDefaultKeys()
{
	irr::SKeyMap	keyMap[5];
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

	m_cameraAnimator->setKeyMap(keyMap, 5);
}

void	Camera::setPosition(const ecs::Position & newPosition)
{
	m_camera->setPosition(newPosition.getVectorPosition());
	m_camera->setRotation(newPosition.getVectorRotation());
	m_camera->setScale(newPosition.getVectorScale());
}

void Camera::setSpeed(const irr::f32 speed)
{
	m_cameraAnimator->setMoveSpeed(speed);
}
