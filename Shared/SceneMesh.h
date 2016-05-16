#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneMesh : public AScene
	{
	public:
		SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, bool isCollisionable, const std::string& namePK3 = "");
		virtual ~SceneMesh();

		virtual	void			setPosition(const Position& newPosition);

		void					setCollision();

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		irr::scene::IMeshSceneNode*	m_node;
	};
}
