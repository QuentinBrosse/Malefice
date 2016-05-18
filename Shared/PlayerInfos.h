#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT PlayerInfos : public AComponent
	{
	public:
		PlayerInfos();
		~PlayerInfos()	= default;

		void	init();
		

		const std::string&	getNickname()	const;

		void	setNickname(const std::string& nickname);


		virtual	void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		std::string	m_nickname;
	};
}
