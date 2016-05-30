#pragma once

#include <BitStream.h>
#include "AScene.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SceneBillboardText : public AScene
	{
	public:
		SceneBillboardText();
		SceneBillboardText(const SceneBillboardText& cpy);
		SceneBillboardText(irr::IrrlichtDevice* device, const irr::video::SColor color, std::string text, const ecs::Position position);
		virtual ~SceneBillboardText();

		virtual void	init(irr::IrrlichtDevice* device, const irr::video::SColor color, std::string text, const ecs::Position position);

		virtual irr::scene::ISceneNode*	getNode()	const;
		virtual void		setPosition(const ecs::Position& newPosition);

		void				setParent(irr::scene::ISceneNode* parent);

		virtual AComponent&	affect(const AComponent& rhs);
		virtual AComponent*	createCopy(const AComponent* rhs) const;
		virtual	void		dump(std::ostream& os)	const;
		virtual void		serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void		deserialize(RakNet::BitStream& in);

	private:
		irr::scene::IBillboardTextSceneNode*	m_node;
		std::wstring							m_text;
	};
}
