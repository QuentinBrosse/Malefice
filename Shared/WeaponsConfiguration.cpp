#include <exception>
#include "WeaponsConfiguration.h"
#include "Logger.h"

bool	WeaponsConfiguration::loadFromFile(const std::string& filepath)
{
	tinyxml2::XMLDocument	doc;
	tinyxml2::XMLElement*	weaponsElement;
	tinyxml2::XMLError		loadResult = doc.LoadFile(filepath.c_str());

	if (loadResult != tinyxml2::XMLError::XML_SUCCESS)
	{
		LOG_CRITICAL << "Weapons configuration file could not be read properly (error code: " << loadResult << ").";
		return false;
	}
	weaponsElement = doc.RootElement();
	if (weaponsElement == nullptr)
	{
		LOG_CRITICAL << "Weapons configuration file could not be read properly (error code: " << doc.ErrorID() << ").";
		return false;
	}
	for (tinyxml2::XMLElement* currentWeapon = weaponsElement->FirstChildElement(); currentWeapon != nullptr; currentWeapon = currentWeapon->NextSiblingElement())
	{
		int						id = 0;
		ecs::Weapon::WeaponType	type;
		std::string				name;
		int						maxAmmunition;
		int						maxAmmunitionExplosive;
		int						maxAmmunitionLoader;
		int						maxAmmunitionExplosiveLoader;
		int						damage;
		int						damageExplosive;
		std::string				handToHandStr;
		bool					handToHand;

		if (currentWeapon->QueryIntAttribute("id", &id) != tinyxml2::XMLError::XML_NO_ERROR || id <= 0)
		{
			LOG_ERROR << "Bad weapon ID \"" << id << "\", skipping element.";
			continue;
		}
		name = this->getOrCreateElementString(doc, *currentWeapon, "name", "");
		type = this->parseWeaponType(this->getOrCreateElementString(doc, *currentWeapon, "type", ""));
		maxAmmunition = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "maxAmmunition", "-1"));
		maxAmmunitionExplosive = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "maxAmmunitionExplosive", "-1"));
		maxAmmunitionLoader = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "maxAmmunitionLoader", "-1"));
		maxAmmunitionExplosiveLoader = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "maxAmmunitionExplosiveLoader", "-1"));
		damage = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "damage", "-1"));
		damageExplosive = std::stoi(this->getOrCreateElementString(doc, *currentWeapon, "damageExplosive", "-1"));
		handToHandStr = this->getOrCreateElementString(doc, *currentWeapon, "handToHand", "");
		if (handToHandStr != "TRUE" && handToHandStr != "FALSE")
		{
			LOG_ERROR << "Bad weapon \"handToHand\" value \"" << handToHandStr << "\", skipping element.";
			continue;
		}
		else
		{
			handToHand = (handToHandStr == "TRUE" ? true : false);
		}
		if (name == "" || type == ecs::Weapon::WEAPON_COUNT || maxAmmunition <= -1 || maxAmmunitionExplosive <= -1 || maxAmmunitionLoader <= -1 || maxAmmunitionExplosiveLoader <= -1 || damage <= -1 || damageExplosive <= -1)
		{
			LOG_ERROR << "Bad weapon element value, skipping element.";
			continue;
		}
		m_weapons.emplace(std::piecewise_construct, std::make_tuple(type), std::make_tuple(id, name, maxAmmunition, maxAmmunitionExplosive, damage, damageExplosive, maxAmmunitionLoader, maxAmmunitionExplosiveLoader, type, handToHand));
	}
	return true;
}

bool	WeaponsConfiguration::saveToFile(const std::string& filepath)	const
{
	throw std::logic_error("WeaponsConfiguration::saveToFile() not implemented");
}


const std::map<ecs::Weapon::WeaponType, ecs::Weapon>	&WeaponsConfiguration::getWeapons()	const
{
	return m_weapons;
}


ecs::Weapon::WeaponType	WeaponsConfiguration::parseWeaponType(const std::string& weaponTypeStr)	const
{
	std::map<std::string, ecs::Weapon::WeaponType>	weaponTypes;
	auto											weaponType = weaponTypes.end();

	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SNIPER_RIFLE", ecs::Weapon::WeaponType::SNIPER_RIFLE));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("RAIL_GUN", ecs::Weapon::WeaponType::RAIL_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SHOTGUN", ecs::Weapon::WeaponType::SHOTGUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("MACHINE_GUN", ecs::Weapon::WeaponType::MACHINE_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("REVOLVER", ecs::Weapon::WeaponType::REVOLVER));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("DOUBLE_GUN", ecs::Weapon::WeaponType::DOUBLE_GUN));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("SABER", ecs::Weapon::WeaponType::SABER));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("CHAIN_SAW", ecs::Weapon::WeaponType::CHAIN_SAW));
	weaponTypes.insert(std::make_pair<std::string, ecs::Weapon::WeaponType>("KNIFE", ecs::Weapon::WeaponType::KNIFE));
	weaponType = weaponTypes.find(weaponTypeStr);
	if (weaponType != weaponTypes.end())
		return weaponType->second;
	else
		return ecs::Weapon::WeaponType::WEAPON_COUNT;
}
