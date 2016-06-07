#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneMesh : public AScene
	{
	public:
		SceneMesh();
		SceneMesh(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, bool isCollisionable, const std::string& namePK3 = "");
		SceneMesh(const SceneMesh& cpy);
		virtual ~SceneMesh();

		virtual void	init(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const int newPickableFlags, bool isCollisionable, const std::string& namePK3 = "");

		virtual irr::scene::ISceneNode*	getNode()	const;
		virtual	void			setPosition(const Position& newPosition);

		virtual AComponent&		affect(const AComponent& rhs);

		void					setCollision(bool gratity);

		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

		virtual AComponent*	createCopy(const AComponent* rhs) const;
	private:
		irr::scene::IMeshSceneNode*	m_node;
	};
}
