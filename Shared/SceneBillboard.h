#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneBillboard : public AScene
	{
	public:
		SceneBillboard();
		SceneBillboard(const SceneBillboard& cpy);
		SceneBillboard(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh);
		virtual ~SceneBillboard();

		virtual void	init(irr::IrrlichtDevice* device, const std::string& newNameTexture, const bool lighting, const irr::u32 level);

		virtual irr::scene::ISceneNode*	getNode()	const;
		virtual void	setPosition(const ecs::Position& newPosition);

		void setTexture(const std::string & nameTexture);

		virtual	void	dump(std::ostream& os)	const;

		virtual AComponent&	affect(const AComponent& rhs);

		virtual AComponent*	createCopy(const AComponent* rhs) const;
		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

	private:
		irr::scene::IBillboardSceneNode*	m_node;
		bool								m_lighting;
		irr::u32							m_level;
	};
}
