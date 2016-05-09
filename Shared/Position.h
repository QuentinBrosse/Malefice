#pragma once

#include "AComponent.h"
#include <irrlicht.h>
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Position: public AComponent
	{
	public:
		Position(float xPosition, float yPosition, float zPosition, float xRotation, float yRotation, float zRotation);
		Position(const irr::core::vector3df& vectorPosition, const irr::core::vector3df vectorRotation);
		Position(const Position& pos);
		Position& operator=(const Position& pos);
		~Position() = default;

		void					setVectorPosition(float x, float y, float z);
		void					setVectorRotation(float x, float y, float z);
		void					set(const Position& pos);

		irr::core::vector3df	getVectorPosition()					const;
		irr::core::vector3df	getVectorRotation()					const;

		void					dump()								const;

		bool					operator!=(const Position& other)	const;
		bool					operator==(const Position& other)	const;

	private:
		irr::core::vector3df	m_vectorPosition;
		irr::core::vector3df	m_vectorRotation;
	};
}
