#pragma once

#include "AComponent.h"
#include <irrlicht.h>
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Position: public AComponent
	{
	public:
		Position(float xPosition, float yPosition, float zPosition, float xTarget, float yTarget, float zTarget);
		Position(const Position& pos);
		Position& operator=(const Position& pos);
		~Position() = default;

		void					setVectorPosition(float x, float y, float z);
		void					setVectorTarget(float x, float y, float z);
		void					set(const Position& pos);

		irr::core::vector3df	getVectorPosition()					const;
		irr::core::vector3df	getVectorTarget()					const;

		void					dump()								const;

		bool					operator!=(const Position& other)	const;
		bool					operator==(const Position& other)	const;

	private:
		irr::core::vector3df	m_vectorPosition;
		irr::core::vector3df	m_vectorTarget;
	};
}
