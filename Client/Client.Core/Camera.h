#pragma once

#include <irrlicht.h>

#include "AComponent.h"
#include "Position.h"

namespace ecs
{

	class Camera : public AComponent
	{
	public:
		Camera(const Position& position, irr::scene::ISceneManager*	sceneManager);
		Camera(const Camera&) = delete;
		~Camera();

		Position	getPosition()	const;
	private:
		irr::scene::ICameraSceneNode*	m_camera;
	};
}