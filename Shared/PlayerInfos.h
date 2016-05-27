#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"
#include "SceneBillboardText.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT PlayerInfos : public AComponent
	{
	public:
		PlayerInfos();
		PlayerInfos(const PlayerInfos& cpy);
		~PlayerInfos()	= default;

		void	init();
		
		const std::string&	getNickname()	const;
		void				setNickname(const std::string& nickname);

		void				setNicknameNode(ecs::SceneBillboardText* nicknameNode);
		ecs::SceneBillboardText*	getNicknameNode() const;

		virtual	void		dump(std::ostream& os)	const;

		virtual AComponent&	affect(const AComponent& rhs);
		virtual AComponent*	createCopy(const AComponent* rhs) const;

		virtual void		serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void		deserialize(RakNet::BitStream& in);


	private:
		std::string					m_nickname;
		ecs::SceneBillboardText*	m_nicknameNode;
	};
}
