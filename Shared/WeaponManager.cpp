<<<<<<< HEAD
#include "WeaponManager.h"

namespace ecs
{
	WeaponManager::WeaponManager() : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER),
		m_currentWeapon(m_weapons.end())
	{
	}

	WeaponManager::WeaponManager(const WeaponManager& cpy): AComponent("WeaponManager", ComponentType::WEAPON_MANAGER),
		m_currentWeapon(m_weapons.end())
	{
		for (auto weapon : cpy.m_weapons)
		{
			m_weapons[weapon.first] = weapon.second;
		}
		if (!m_weapons.empty() && cpy.m_currentWeapon != cpy.m_weapons.end())
			m_currentWeapon = m_weapons.find(cpy.m_currentWeapon->first);
		else
			m_currentWeapon = m_weapons.end();
	}

	WeaponManager::WeaponManager(Weapon& defaultWeapon) : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER)
	{
		init(defaultWeapon);
	}


	void	WeaponManager::init(Weapon& defaultWeapon)
	{
		m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&>(defaultWeapon.getWeaponType(), defaultWeapon));
		m_currentWeapon = m_weapons.begin();
	}


	void	WeaponManager::addWeapon(Weapon& newWeapon)
	{
		if (m_weapons.find(newWeapon.getWeaponType()) == m_weapons.end())
			m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&>(newWeapon.getWeaponType(), newWeapon));
		else
			m_weapons[newWeapon.getWeaponType()].incAmmunition(newWeapon.getAmmunitions());
		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
	}

	
	void WeaponManager::changeToNextWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		++m_currentWeapon;
		if (m_currentWeapon == m_weapons.end())
			m_currentWeapon = m_weapons.begin();
		m_currentWeapon->second.setActivity(true);
	}

	void WeaponManager::changeToPrecWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		if (m_currentWeapon == m_weapons.begin())
			m_currentWeapon = --(m_weapons.end());
		else
			--m_currentWeapon;
		m_currentWeapon->second.setActivity(true);
	}

	bool	WeaponManager::hasCurrentWeapon() const
	{
		return m_currentWeapon != m_weapons.end();
	}

	Weapon&	WeaponManager::getCurrentWeapon() const
	{
		return m_currentWeapon->second;
	}

	std::map<Weapon::WeaponType, Weapon>& WeaponManager::getWeapons()
	{
		return m_weapons;
	}

	void WeaponManager::createWeapon(irr::IrrlichtDevice* device, const Weapon& weaponCpy)
	{
		Weapon*	weapon = new Weapon(weaponCpy);

		//weapon->createScene(device, false);
		this->addWeapon(*weapon);
		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::dump(std::ostream& os)	const
	{
		os << "WeaponManager {weapons = [";
		for (auto it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			os << "Pair {WeaponType = " << it->first << ", Weapon = ";
			it->second.dump(os);
			os << "}" << (std::next(it) != m_weapons.end() ? ", " : "");
		}
		os << "], currentWeapon = ";
		if (m_currentWeapon != m_weapons.end())
		{
			os << "Pair {WeaponType = " << m_currentWeapon->first << ", Weapon = ";
			m_currentWeapon->second.dump(os);
			os << "}";
		}
		else
		{
			os << "N/A";
		}
		os << "}";
	}

	AComponent& WeaponManager::affect(const AComponent& rhs)
	{
		const WeaponManager& weaponManager = dynamic_cast<const WeaponManager&>(rhs);

		for (auto weapon : weaponManager.m_weapons)
		{
			m_weapons.insert(weapon);
		}
		if (weaponManager.m_currentWeapon != weaponManager.m_weapons.end())
			m_currentWeapon = m_weapons.find(weaponManager.m_currentWeapon->first);
		else
			m_currentWeapon = m_weapons.end();

		return *this;
	}


	void	WeaponManager::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);

		out.Write<size_t>(m_weapons.size());
		for (auto weapon : m_weapons)
		{
			out.Write(weapon.first);
			weapon.second.serialize(out, false);
		}

	if (m_currentWeapon != m_weapons.end())
		{
			out.Write(true);
			out.Write(m_currentWeapon->first);
		}
		else
			out.Write(false);
	}

	void	WeaponManager::deserialize(RakNet::BitStream& in)
	{
		Weapon::WeaponType	weaponType;
		bool				haveCurrent;
		size_t				nbWeapons;

		AComponent::deserialize(in);
		in.Read(nbWeapons);
		for (size_t i = 0; i < nbWeapons; i++)
		{
			in.Read(weaponType);
			m_weapons[weaponType].deserialize(in);
		}
		in.Read(haveCurrent);
		if (haveCurrent)
		{
			in.Read(weaponType);
			m_currentWeapon = m_weapons.find(weaponType);
		}
		else
			m_currentWeapon = m_weapons.end();
	}

	AComponent* WeaponManager::createCopy(const AComponent* rhs) const
	{
		const WeaponManager*	weaponManager = dynamic_cast<const WeaponManager*>(rhs);

		return new WeaponManager(*weaponManager);
	}
};

=======
#include "WeaponManager.h"
#include "WeaponCreator.h"

namespace ecs
{
	WeaponManager::WeaponManager() : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER),
		m_currentWeapon(m_weapons.end())
	{
	}

	WeaponManager::WeaponManager(const WeaponManager& cpy): AComponent("WeaponManager", ComponentType::WEAPON_MANAGER),
		m_currentWeapon(m_weapons.end())
	{
		for (auto weapon : cpy.m_weapons)
		{
			m_weapons[weapon.first] = weapon.second;
		}
		if (!m_weapons.empty() && cpy.m_currentWeapon != cpy.m_weapons.end())
			m_currentWeapon = m_weapons.find(cpy.m_currentWeapon->first);
		else
			m_currentWeapon = m_weapons.end();
	}

	WeaponManager::WeaponManager(Weapon& defaultWeapon) : AComponent("WeaponManager", ecs::AComponent::ComponentType::WEAPON_MANAGER)
	{
		this->init(defaultWeapon);
	}


	void	WeaponManager::init(Weapon& defaultWeapon)
	{
		m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&>(defaultWeapon.getWeaponType(), defaultWeapon));
		m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::reset()
	{
		m_weapons.erase(m_weapons.begin(), m_weapons.end());
		this->init(WeaponCreator::getInstance().create(ecs::Weapon::WeaponType::SHOT_GUN));
	}


	void	WeaponManager::addWeapon(Weapon& newWeapon)
	{
		if (m_weapons.find(newWeapon.getWeaponType()) == m_weapons.end())
			m_weapons.insert(std::pair<Weapon::WeaponType, Weapon&> (newWeapon.getWeaponType(), newWeapon));

		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
	}

	
	void WeaponManager::changeToNextWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		++m_currentWeapon;
		if (m_currentWeapon == m_weapons.end())
			m_currentWeapon = m_weapons.begin();
		m_currentWeapon->second.setActivity(true);
	}

	void WeaponManager::changeToPrecWeapon()
	{
		m_currentWeapon->second.setActivity(false);
		if (m_currentWeapon == m_weapons.begin())
			m_currentWeapon = --(m_weapons.end());
		else
			--m_currentWeapon;
		m_currentWeapon->second.setActivity(true);
	}

	bool	WeaponManager::hasCurrentWeapon() const
	{
		return m_currentWeapon != m_weapons.end();
	}

	Weapon&	WeaponManager::getCurrentWeapon() const
	{
		return m_currentWeapon->second;
	}

	std::map<Weapon::WeaponType, Weapon>& WeaponManager::getWeapons()
	{
		return m_weapons;
	}

	void WeaponManager::createWeapon(irr::IrrlichtDevice* device, const Weapon& weaponCpy)
	{
		Weapon*	weapon = new Weapon(weaponCpy);

		//weapon->createScene(device, false);
		this->addWeapon(*weapon);
		if (m_weapons.size() == 1)
			m_currentWeapon = m_weapons.begin();
	}

	void	WeaponManager::dump(std::ostream& os)	const
	{
		os << "WeaponManager {weapons = [";
		for (auto it = m_weapons.begin(); it != m_weapons.end(); ++it)
		{
			os << "Pair {WeaponType = " << it->first << ", Weapon = ";
			it->second.dump(os);
			os << "}" << (std::next(it) != m_weapons.end() ? ", " : "");
		}
		os << "], currentWeapon = ";
		if (m_currentWeapon != m_weapons.end())
		{
			os << "Pair {WeaponType = " << m_currentWeapon->first << ", Weapon = ";
			m_currentWeapon->second.dump(os);
			os << "}";
		}
		else
		{
			os << "N/A";
		}
		os << "}";
	}

	AComponent& WeaponManager::affect(const AComponent& rhs)
	{
		const WeaponManager& weaponManager = dynamic_cast<const WeaponManager&>(rhs);

		for (auto weapon : weaponManager.m_weapons)
		{
			m_weapons.insert(weapon);
		}
		if (weaponManager.m_currentWeapon != weaponManager.m_weapons.end())
			m_currentWeapon = m_weapons.find(weaponManager.m_currentWeapon->first);
		else
			m_currentWeapon = m_weapons.end();

		return *this;
	}


	void	WeaponManager::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);

		out.Write<size_t>(m_weapons.size());
		for (auto weapon : m_weapons)
		{
			out.Write(weapon.first);
			weapon.second.serialize(out, false);
		}

	if (m_currentWeapon != m_weapons.end())
		{
			out.Write(true);
			out.Write(m_currentWeapon->first);
		}
		else
			out.Write(false);
	}

	void	WeaponManager::deserialize(RakNet::BitStream& in)
	{
		Weapon::WeaponType	weaponType;
		bool				haveCurrent;
		size_t				nbWeapons;

		AComponent::deserialize(in);
		in.Read(nbWeapons);
		for (size_t i = 0; i < nbWeapons; i++)
		{
			in.Read(weaponType);
			m_weapons[weaponType].deserialize(in);
		}
		in.Read(haveCurrent);
		if (haveCurrent)
		{
			in.Read(weaponType);
			m_currentWeapon = m_weapons.find(weaponType);
		}
		else
			m_currentWeapon = m_weapons.end();
	}

	AComponent* WeaponManager::createCopy(const AComponent* rhs) const
	{
		const WeaponManager*	weaponManager = dynamic_cast<const WeaponManager*>(rhs);

		return new WeaponManager(*weaponManager);
	}
};

>>>>>>> 02a6c0ba10dcff55aefa7b4284ff108ea75c6230
