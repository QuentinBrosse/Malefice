#include "PlayerInfos.h"

ecs::PlayerInfos::PlayerInfos() : AComponent("PlayerInfos", ecs::AComponent::ComponentType::PLAYER_INFOS),
	m_nickname()
{
}

ecs::PlayerInfos::PlayerInfos(const PlayerInfos& cpy) : AComponent("PlayerInfos", ecs::AComponent::ComponentType::PLAYER_INFOS),
	m_nickname(cpy.getNickname())
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

void ecs::PlayerInfos::setNicknameNode(ecs::SceneBillboardText* nicknameNode)
{
	m_nicknameNode = nicknameNode;
}

ecs::SceneBillboardText*	ecs::PlayerInfos::getNicknameNode() const
{
	return m_nicknameNode;
}


void	ecs::PlayerInfos::dump(std::ostream& os)	const
{
	os << "PlayerInfos {nickname = \"" << m_nickname << "\"}";
}

ecs::AComponent&	ecs::PlayerInfos::affect(const AComponent& rhs)
{
	const PlayerInfos&	player = dynamic_cast<const PlayerInfos&>(rhs);

	m_nickname = player.m_nickname;
	return *this;
}

ecs::AComponent*	ecs::PlayerInfos::createCopy(const ecs::AComponent* rhs) const
{
	const ecs::PlayerInfos* playerInfos = dynamic_cast<const ecs::PlayerInfos *>(rhs);
	return new ecs::PlayerInfos(*playerInfos);
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
