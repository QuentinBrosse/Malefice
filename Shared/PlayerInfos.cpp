#include "PlayerInfos.h"

ecs::PlayerInfos::PlayerInfos() : AComponent("PlayerInfos", ecs::AComponent::ComponentType::PLAYER_INFOS),
	m_nickname()
{
}

void	ecs::PlayerInfos::init()
{
}


const std::string&	ecs::PlayerInfos::getNickname()	const
{
	return m_nickname;
}


void	ecs::PlayerInfos::setNickname(const std::string& nickname)
{
	m_nickname = nickname;
}


void	ecs::PlayerInfos::dump(std::ostream& os)	const
{
	os << "PlayerInfos {nickname = \"" << m_nickname << "\"}";
}

ecs::AComponent& ecs::PlayerInfos::affect(const AComponent & rhs)
{
	const PlayerInfos&	player = dynamic_cast<const PlayerInfos&>(rhs);

	m_nickname = player.m_nickname;
	return *this;
}


void	ecs::PlayerInfos::serialize(RakNet::BitStream& out, bool serializeType)	const
{
	AComponent::serialize(out);
	out.Write(RakNet::RakString(m_nickname.c_str()));
}

void	ecs::PlayerInfos::deserialize(RakNet::BitStream& in)
{
	RakNet::RakString	nickname;

	in.Read(nickname);
	m_nickname = nickname.C_String();
}
