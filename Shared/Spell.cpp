#include <iostream>
#include "Spell.h"

namespace ecs
{
	Spell::Spell() : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(0), m_name("default"), m_cooldown(0), m_spellType(Spell::NOTHING), m_isLock(false), m_duration(0)
	{
	}

	Spell::Spell(const int id, const std::string& name, const Spell::SpellType spellType, const size_t coolDown, const std::size_t duration) : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(id), m_name(name), m_spellType(spellType), m_cooldown(coolDown), m_isLock(false), m_duration(m_cooldown)
	{
	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(cpy.m_id), m_name(cpy.m_name), m_spellType(cpy.m_spellType), m_cooldown(cpy.m_cooldown), m_isLock(false)
	{
	}


	void	Spell::init(const int id, const std::string& name, const SpellType spellType, const std::size_t coolDown, const std::size_t duration)
	{
		m_id = id;
		m_name = name;
		m_spellType = spellType;
		m_cooldown = coolDown;
		m_isLock = false;
		m_duration = duration;
	}


	const Spell::SpellType	Spell::getSpellType() const
	{
		return m_spellType;
	}

	void Spell::setSpellType(const SpellType newSpellType)
	{
		m_spellType = newSpellType;
	}

	bool Spell::isLock() const
	{
		return m_isLock;
	}

	void Spell::lock()
	{
		m_isLock = true;
	}

	void Spell::unlock()
	{
		m_isLock = false;
	}

	AComponent& Spell::affect(const AComponent& rhs)
	{
		const Spell&	spell = dynamic_cast<const Spell&>(rhs);

		m_id = spell.m_id;
		m_name = spell.m_name;
		m_cooldown = spell.m_cooldown;
		m_spellType = spell.m_spellType;
		m_isLock = spell.m_isLock;
		m_duration = spell.m_duration;
		return *this;
	}


	void	Spell::dump(std::ostream& os)	const
	{
		os << "Spell {ID = " << Spell::m_id << ", SPELL_NAME = \"" << Spell::m_name << "\", COOLDOWN = " << Spell::m_cooldown << ", spellType = " << m_spellType << ", isLock = " << m_isLock << "}";
	}


	void	Spell::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_id);
		out.Write(RakNet::RakString(m_name.c_str()));
		out.Write(m_cooldown);
		out.Write(m_spellType);
		out.Write(m_isLock);
		out.Write(m_duration);
	}

	void	Spell::deserialize(RakNet::BitStream& in)
	{
		RakNet::RakString	name;

		AComponent::deserialize(in);
		in.Read(m_id);
		in.Read(name);
		in.Read(m_cooldown);
		in.Read(m_spellType);
		in.Read(m_isLock);
		in.Read(m_duration);
		m_name = name.C_String();
	}

	AComponent * Spell::createCopy(const AComponent * rhs) const
	{
		const Spell*	spell = dynamic_cast<const Spell*>(rhs);

		return new Spell(*spell);
	}
}
