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
	void							init();
	void					loadKey(const ecs::Position& position, irr::scene::ISceneManager* sceneManager, bool normalKey);

private:
	irr::scene::ICameraSceneNode*	m_camera;
};