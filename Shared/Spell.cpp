#include <iostream>
#include "Spell.h"

namespace ecs
{
	Spell::Spell() : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(0), m_name("default"), m_cooldown(0), m_spellType(Spell::NOTHING), m_isLock(false)
	{
	}

	Spell::Spell(const int id, const std::string& name, const Spell::SpellType spellType, const int coolDown) : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(id), m_name(name), m_spellType(spellType), m_cooldown(coolDown)
	{
		m_isLock = false;
	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(cpy.m_id), m_name(cpy.m_name), m_spellType(cpy.m_spellType), m_cooldown(cpy.m_cooldown)
	{
		m_isLock = false;
	}


	void	Spell::init()
	{
		// TODO: implement constructor logic here
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
		m_name = name.C_String();
	}
}
