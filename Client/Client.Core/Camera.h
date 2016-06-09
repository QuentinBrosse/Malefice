#pragma once

#include <irrlicht.h>

#include "AComponent.h"
#include "Position.h"
#include "NodePickable.h"

class Camera
{
public:
	Camera(const ecs::Position& position, irr::scene::ISceneManager* sceneManager);
	Camera(const Camera&) = delete;
	~Camera();

	ecs::Position					getPosition()		const;
	ecs::Position					getPositionTarget()	const;
	irr::core::vector3df			getTarget()			const;
	irr::scene::ICameraSceneNode*	getNode()			const;

	void							init(const ecs::Position& position, irr::scene::ISceneManager* sceneManager);
	void							loadDefaultKeys();
	void							loadInvertKeys();
	void							setPosition(const ecs::Position& newPosition);
	void							setFov(const irr::f32 fov);

	void							setSpeed(const irr::f32 speedMove, const irr::f32 speedRotation);

	void							zoom();
	void							unZoom();

	bool							isInZoom()	const;
private:
	irr::scene::ICameraSceneNode*				m_camera;
	irr::scene::ISceneNodeAnimatorCameraFPS*	m_cameraAnimator;
	bool										m_isInZoom;
};