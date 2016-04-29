#pragma once

#include "Entity.h"
#include "CollectionComponent.h"
#include "Position.h"

namespace factory
{
	class ObjectFactory
	{
	public:
		ObjectFactory() = delete;
		~ObjectFactory() = delete;

		static ecs::Entity createObject(float x, float y, float z);
	private:

	};
}