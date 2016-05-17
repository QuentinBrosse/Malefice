#pragma once

#include <irrlicht.h>
#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Position: public AComponent
	{
	public:
		Position();
		Position(float xPosition, float yPosition, float zPosition, float xRotation, float yRotation, float zRotation, float xScale = 1.0f, float yScale = 1.0f, float zScale = 1.0f);
		Position(const irr::core::vector3df& vectorPosition, const irr::core::vector3df& vectorRotation, const irr::core::vector3df& vectorScale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
		Position(const Position& pos);
		Position& operator=(const Position& pos);
		~Position() = default;

		virtual void	init();

		void					setVectorPosition(const irr::core::vector3df& newVectorPosition);
		void					setVectorRotation(const irr::core::vector3df& newVectorRotation);
		void					setVectorScale(const irr::core::vector3df& newVectorScale);
		void					set(const Position& pos);

		irr::core::vector3df	getVectorPosition()					const;
		irr::core::vector3df	getVectorRotation()					const;
		irr::core::vector3df	getVectorScale()					const;

		bool					operator!=(const Position& other)	const;
		bool					operator==(const Position& other)	const;


		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		irr::core::vector3df	m_vectorPosition;
		irr::core::vector3df	m_vectorRotation;
		irr::core::vector3df	m_vectorScale;
	};
}
