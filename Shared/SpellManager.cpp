#include <iterator>
#include "SpellManager.h"
#include "WeaponCreator.h"
#include "TimeUtility.h"
#include "SpellCreator.h"

namespace ecs
{
	SpellManager::SpellManager() : AComponent("SpellManager", ecs::AComponent::ComponentType::SPELL_MANAGER),
		m_spells(), m_currentSpell(m_spells.end()), m_weaponManager(), m_weaponsIsCurrent(false), m_cooldown(20), m_cooldownEndTime(0)
	{
		SpellCreator& spellCreator = SpellCreator::getInstance();
		m_spells.insert(std::make_pair(Spell::SpellType::BLIND, spellCreator.create(Spell::SpellType::BLIND)));
		m_spells.insert(std::make_pair(Spell::SpellType::CONFUSION, spellCreator.create(Spell::SpellType::CONFUSION)));
		m_spells.insert(std::make_pair(Spell::SpellType::DEAF, spellCreator.create(Spell::SpellType::DEAF)));
		m_spells.insert(std::make_pair(Spell::SpellType::PARANOIA, spellCreator.create(Spell::SpellType::PARANOIA)));
		m_spells.insert(std::make_pair(Spell::SpellType::PARKINSON, spellCreator.create(Spell::SpellType::PARKINSON)));
		m_spells.insert(std::make_pair(Spell::SpellType::SLOW, spellCreator.create(Spell::SpellType::SLOW)));
		m_currentSpell = m_spells.begin();
		m_weaponManager.addWeapon(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::SHOT_GUN));
	}

	SpellManager::SpellManager(const SpellManager& cpy) : AComponent("SpellManager", ComponentType::SPELL_MANAGER),
		m_currentSpell(m_spells.end()), m_weaponManager(), m_weaponsIsCurrent(cpy.m_weaponsIsCurrent), m_cooldown(cpy.m_cooldown), m_cooldownEndTime(cpy.m_cooldownEndTime)
	{
		for (auto& spell : cpy.m_spells)
		{
			m_spells[spell.first].affect(spell.second);
		}
		if (!m_spells.empty() && cpy.m_currentSpell != cpy.m_spells.end())
			m_currentSpell = m_spells.find(cpy.m_currentSpell->first);
		else
			m_currentSpell = m_spells.end();
		m_weaponManager.affect(cpy.m_weaponManager);
	}

	//TODO: CHange new Weapon with call to WeaponCreator
	SpellManager::SpellManager(const Spell& defaultSpell, const int cooldown) : AComponent("SpellManager", ecs::AComponent::ComponentType::SPELL_MANAGER),
		m_spells(), m_currentSpell(m_spells.end()), m_weaponManager(), m_weaponsIsCurrent(false), m_cooldown(cooldown), m_cooldownEndTime(0)
	{
		m_spells.insert(std::pair<Spell::SpellType, Spell>(defaultSpell.getSpellType(), defaultSpell));
		m_currentSpell = m_spells.begin();
		m_weaponManager.addWeapon(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::SHOT_GUN));
		//m_weaponManager.addWeapon(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::KNIFE));
	}


	void	SpellManager::init(const Spell& defaultSpell, const int cooldown)
	{
		m_spells.insert(std::pair<Spell::SpellType, Spell>(defaultSpell.getSpellType(), defaultSpell));
		m_currentSpell = m_spells.begin();
		m_weaponsIsCurrent = false;
		m_weaponManager.addWeapon(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::SHOT_GUN));
		m_weaponManager.addWeapon(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::KNIFE));
		m_cooldown = cooldown;
		m_cooldownEndTime = 0;
	}


	Spell& SpellManager::getCurrentSpell() const
	{
		return m_currentSpell->second;
	}

	bool SpellManager::weaponsIsCurrent() const
	{
		return m_weaponsIsCurrent;
	}

	long long SpellManager::getCooldownEndTime() const
	{
		return m_cooldownEndTime;
	}

	int SpellManager::getCooldown() const
	{
		return m_cooldown;
	}

	bool SpellManager::isLock() const
	{
		return m_cooldownEndTime < utility::TimeUtility::getMsTime() && m_cooldownEndTime != 0;
	}

	void SpellManager::setCooldownEndTime(const long long cooldownEndTime)
	{
		m_cooldownEndTime = cooldownEndTime;
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

	bool	SpellManager::hasCurrentWeapon()	const
	{
		return m_weaponManager.hasCurrentWeapon();
	}

	Weapon& SpellManager::getCurrentWeapon() const
	{
		return m_weaponManager.getCurrentWeapon();
	}

	std::map<Spell::SpellType, Spell>& SpellManager::getSpells()
	{
		return m_spells;
	}

	void SpellManager::changeToNextWeapon()
	{
		m_weaponManager.changeToNextWeapon();
	}

	void SpellManager::changeToPrecWeapon()
	{
		m_weaponManager.changeToPrecWeapon();
	}

	void SpellManager::createFPSScene(irr::IrrlichtDevice * device, irr::scene::ISceneNode * parent)
	{
		SceneAnimatedMesh*	scene;

		for (auto& spell : m_spells)
		{
			if (spell.second.getScene() == nullptr)
			{
				spell.second.createScene(device, parent, false);
				scene = spell.second.getScene();
				scene->setPosition(spell.second.getFPSMetrics());
			}
			spell.second.setActivity(false);
		}
		if (m_currentSpell != m_spells.end() && !m_weaponsIsCurrent)
			m_currentSpell->second.setActivity(true);
		for (auto& weapon : m_weaponManager.getWeapons())
		{
			if (weapon.second.getScene() != nullptr)
				continue;
			weapon.second.createScene(device, parent, false);
			scene = weapon.second.getScene();
			scene->setPosition(weapon.second.getFPSMetrics());
		}
		//TODO: create spell's scenes
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
		m_weaponManager.affect(spellManager.m_weaponManager);
		for (auto& spell : spellManager.m_spells)
			m_spells[spell.first].affect(spell.second);
		if (spellManager.m_currentSpell != spellManager.m_spells.end())
			m_currentSpell = m_spells.find(spellManager.m_currentSpell->first);
		else
			m_currentSpell = m_spells.end();
		m_cooldown = spellManager.m_cooldown;
		m_cooldownEndTime = spellManager.m_cooldownEndTime;

		return *this;
	}

	void	SpellManager::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		m_weaponManager.serialize(out, false);
		out.Write(m_weaponsIsCurrent);
		out.Write<size_t>(m_spells.size());
		for (auto it = m_spells.begin(); it != m_spells.end(); it++)
		{
			out.Write(it->first);
			it->second.serialize(out, false);
		}
		if (m_currentSpell != m_spells.end())
		{
			out.Write(true);
			out.Write(m_currentSpell->first);
		}
		else
			out.Write(false);
		out.Write(m_cooldown);
		out.Write(m_cooldownEndTime);
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
		in.Read(m_cooldown);
		in.Read(m_cooldownEndTime);
	}

	AComponent * SpellManager::createCopy(const AComponent* rhs) const
	{
		const SpellManager* spellManager = dynamic_cast<const SpellManager*>(rhs);

		return new SpellManager(*spellManager);
	}
}
