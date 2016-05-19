#include <iterator>
#include "SpellManager.h"

namespace ecs
{
	SpellManager::SpellManager() : AComponent("SpellManager", ecs::AComponent::ComponentType::SPELL_MANAGER),
		m_spells(), m_currentSpell(m_spells.end()), m_weaponManager(), m_weaponsIsCurrent(false)
	{
	}

	SpellManager::SpellManager(const SpellManager & cpy) : AComponent("SpellManager", ComponentType::SPELL_MANAGER),
		m_currentSpell(cpy.m_currentSpell), m_spells(cpy.m_spells), m_weaponManager(cpy.m_weaponManager), m_weaponsIsCurrent(cpy.m_weaponsIsCurrent)
	{
	}

	//TODO: CHange new Weapon with call to WeaponCreator
	SpellManager::SpellManager(const Spell& defaultSpell) : AComponent("SpellManager", ecs::AComponent::ComponentType::SPELL_MANAGER),
		m_spells(), m_currentSpell(m_spells.end()), m_weaponManager(*(new Weapon()))
	{
	}


	void	SpellManager::init(const Spell& defaultSpell)
	{
		m_spells.insert(std::pair<Spell::SpellType, Spell>(defaultSpell.getSpellType(), defaultSpell));
		m_currentSpell = m_spells.begin();
		m_weaponManager.addWeapon(*(new Weapon()));
		// TODO: Change new Weapon() with two weapons of predator
	}


	Spell& SpellManager::getCurrentSpell() const
	{
		return m_currentSpell->second;
	}

	bool SpellManager::weaponsIsCurrent() const
	{
		return m_weaponsIsCurrent;
	}

	void SpellManager::changeCurrentManager()
	{
		m_weaponsIsCurrent = !m_weaponsIsCurrent;
	}

	void SpellManager::addSpell(const Spell& newSpell)
	{
		if (m_spells.find(newSpell.getSpellType()) == m_spells.end())
			m_spells.insert(std::pair<Spell::SpellType, Spell>(newSpell.getSpellType(), newSpell));
	}

	void SpellManager::changeToNextSpell()
	{
		++m_currentSpell;
		if (m_currentSpell == m_spells.end())
			m_currentSpell = m_spells.begin();
	}

	void SpellManager::changeToPrecSpell()
	{
		if (m_currentSpell == m_spells.begin())
			m_currentSpell = --(m_spells.end());
		else
			--m_currentSpell;
	}

	Weapon& SpellManager::getCurrentWeapon() const
	{
		return m_weaponManager.getCurrentWeapon();
	}

	void SpellManager::changeToNextWeapon()
	{
		m_weaponManager.changeToNextWeapon();
	}

	void SpellManager::changeToPrecWeapon()
	{
		m_weaponManager.changeToPrecWeapon();
	}


	void	SpellManager::dump(std::ostream& os)	const
	{
		os << "SpellManager {spells = [";
		for (auto it = m_spells.begin(); it != m_spells.end(); ++it)
		{
			os << "Pair {SpellType = " << it->first << ", Spell = ";
			it->second.dump(os);
			os << "}" << (std::next(it) != m_spells.end() ? ", " : "");
		}
		os << "], currentSpell = ";
		if (m_currentSpell != m_spells.end())
		{
			os << "Pair {SpellType = " << m_currentSpell->first << ", Spell = ";
			m_currentSpell->second.dump(os);
			os << "}";
		}
		else
		{
			os << "N/A";
		}
		os << ", weaponManager = " << m_weaponManager << ", weaponIsCurrent = " << m_weaponsIsCurrent << "}";
	}

	AComponent& SpellManager::affect(const AComponent& rhs)
	{
		// TODO: insérer une instruction return ici
		const SpellManager&	spellManager = dynamic_cast<const SpellManager&>(rhs);

		m_weaponsIsCurrent = spellManager.m_weaponsIsCurrent;
		m_currentSpell = spellManager.m_currentSpell;
		m_spells = spellManager.m_spells;
		m_weaponManager = spellManager.m_weaponManager;

		return *this;
	}

	void	SpellManager::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		m_weaponManager.serialize(out, serializeType);
		out.Write(m_weaponsIsCurrent);
		out.Write<size_t>(m_spells.size());
		for (auto it = m_spells.begin(); it != m_spells.end(); it++)
		{
			out.Write(it->first);
			it->second.serialize(out, serializeType);
		}
		if (m_currentSpell != m_spells.end())
		{
			out.Write(true);
			out.Write(m_currentSpell->first);
		}
		else
			out.Write(false);

	}

	void	SpellManager::deserialize(RakNet::BitStream& in)
	{
		Spell::SpellType current_spell_type;
		Spell::SpellType spell_type;
		size_t nb_spell;
		bool	haveCurrentSpell;

		AComponent::deserialize(in);
		m_weaponManager.deserialize(in);
		in.Read(m_weaponsIsCurrent);
		in.Read(nb_spell);
		for (size_t i = 0; i < nb_spell; i++)
		{
			in.Read(spell_type);
			m_spells[spell_type].deserialize(in);
		}
		in.Read(haveCurrentSpell);
		if (haveCurrentSpell)
		{
			in.Read(current_spell_type);
			m_currentSpell = m_spells.find(current_spell_type);
		}
		else
			m_currentSpell = m_spells.end();
	}

	AComponent * SpellManager::createCopy(const AComponent * rhs) const
	{
		const SpellManager* spellManager = dynamic_cast<const SpellManager*>(rhs);

		return new SpellManager(*spellManager);
	}
}
