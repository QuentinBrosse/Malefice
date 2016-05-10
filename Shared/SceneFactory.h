#pragma once

#include "Entity.h"

class MALEFICE_DLL_EXPORT SceneFactory
{
public:
	SceneFactory() = delete;
	~SceneFactory() = delete;

	static ecs::Entity *creatScene(const float xPosition, const float yPosition, const float zPosition, const float xTarget, const float yTarget, const float zTarget, const ecs::NetworkID netID);
};