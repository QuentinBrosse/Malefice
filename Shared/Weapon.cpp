#include "Weapon.h"
#include "NodePickable.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		ID(0), WEAPON_NAME(""), MAX_AMMUNITION(0), DAMAGE(0), WEAPON_TYPE(WeaponType::DEFAULT), m_sight(false), m_ammunition(0), m_reloadTime(0), m_ammoPerShot(0), m_fireRate(0), m_distance(0), m_fpsMetricsPosition(0, 0, 0), m_fpsMetricsRotation(0, 0, 0), m_fpsMetricsScale(0, 0, 0), m_externalMetricsPosition(0, 0, 0), m_externalMetricsRotation(0, 0, 0), m_externalMetricsScale(0, 0, 0), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const int id, const std::string& name, WeaponType weaponType, float distance, float precision, unsigned int ammunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, irr::core::vector3df	fpsMetricsPosition, irr::core::vector3df fpsMetricsRotation, irr::core::vector3df fpsMetricsScale, irr::core::vector3df	externalMetricsPosition, irr::core::vector3df externalMetricsRotation, irr::core::vector3df	externalMetricsScale, bool sight) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		ID(id), WEAPON_NAME(name), MAX_AMMUNITION(ammunition), DAMAGE(damage), WEAPON_TYPE(weaponType), m_sight(sight), m_ammunition(ammunition), m_reloadTime(reloadTime), m_ammoPerShot(ammoPerShot), m_fireRate(fireRate), m_distance(distance), m_fpsMetricsPosition(fpsMetricsPosition), m_fpsMetricsRotation(fpsMetricsRotation), m_fpsMetricsScale(fpsMetricsScale), m_externalMetricsPosition(externalMetricsPosition), m_externalMetricsRotation(externalMetricsRotation), m_externalMetricsScale(externalMetricsScale), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		ID(cpy.getId()), WEAPON_NAME(cpy.getName()), MAX_AMMUNITION(cpy.getMaxAmmunitions()), DAMAGE(cpy.getDamage()), WEAPON_TYPE(cpy.getWeaponType()), m_sight(cpy.isSight()), m_ammunition(cpy.getAmmunitions()), m_reloadTime(cpy.getReloadTime()), m_ammoPerShot(cpy.getAmmoPerShot()), m_fireRate(cpy.getFireRate()), m_distance(cpy.getDistance()), m_fpsMetricsPosition(cpy.getFPSMetricsPosition()), m_fpsMetricsRotation(cpy.getFPSMetricsRotation()), m_fpsMetricsScale(cpy.getFPSMetricsScale()), m_externalMetricsPosition(cpy.getExternalMetricsPosition()), m_externalMetricsRotation(cpy.getExternalMetricsRotation()), m_externalMetricsScale(cpy.getExternalMetricsScale()), m_scene(nullptr)
	{

	}

	Weapon& Weapon::operator=(const Weapon& other)
	{
		m_scene = other.m_scene;
		return *this;
	}

	const bool Weapon::isSight() const
	{
		return m_sight;
	}

	const unsigned int Weapon::getReloadTime() const
	{
		return m_reloadTime;
	}

	const unsigned int Weapon::getAmmunitions() const
	{
		return m_ammunition;
	}

	const unsigned int Weapon::getMaxAmmunitions() const
	{
		return MAX_AMMUNITION;
	}

	const unsigned int Weapon::getAmmoPerShot() const
	{
		return m_ammoPerShot;
	}

	const float	Weapon::getFireRate() const
	{
		return m_fireRate;
	}

	const float Weapon::getDistance() const
	{
		return m_distance;
	}

	irr::core::vector3df Weapon::getFPSMetricsPosition() const
	{
		return m_fpsMetricsPosition;
	}

	irr::core::vector3df Weapon::getFPSMetricsRotation() const
	{
		return m_fpsMetricsRotation;
	}

	irr::core::vector3df Weapon::getFPSMetricsScale() const
	{
		return m_fpsMetricsScale;
	}

	irr::core::vector3df Weapon::getExternalMetricsPosition() const
	{
		return m_externalMetricsPosition;
	}

	irr::core::vector3df Weapon::getExternalMetricsRotation() const
	{
		return m_externalMetricsRotation;
	}

	irr::core::vector3df Weapon::getExternalMetricsScale() const
	{
		return m_externalMetricsScale;
	}

	const int Weapon::getId() const
	{
		return ID;
	}

	const std::string & Weapon::getName() const
	{
		return WEAPON_NAME;
	}

	const int		Weapon::getDamage() const
	{
		return DAMAGE;
	}

	void Weapon::shot()
	{
		this->decAmmunition(m_ammoPerShot);
	}

	void Weapon::reload()
	{
		std::cout << "Non implementer" << std::endl;
	}

	const Weapon::WeaponType Weapon::getWeaponType() const
	{
		return WEAPON_TYPE;
	}

	void Weapon::decAmmunition(int nbLoaded)
	{
		if (nbLoaded >= m_ammunition)
			m_ammunition = 0;
		else
			m_ammunition -= nbLoaded;
	}

	void Weapon::incAmmunition(int nbAmmuition)
	{
		m_ammunition += nbAmmuition;
		if (m_ammunition > MAX_AMMUNITION)
			m_ammunition = MAX_AMMUNITION;
	}

	void Weapon::createScene(irr::IrrlichtDevice* device, const std::string& newNameTexture, const std::string& newNameMesh, const bool active)
	{
		if (m_scene)
			delete m_scene;
		device->getSceneManager()->getActiveCamera();
		m_scene = new SceneAnimatedMesh(device, device->getSceneManager()->getActiveCamera(), newNameTexture, newNameMesh, nodePickable::NOT_PICKABLE, true);

	
		m_scene->getScene()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		m_scene->getScene()->setName(newNameMesh.c_str());

		setActivity(active);
	}

	void	Weapon::setActivity(const bool active)
	{
		m_scene->getScene()->setVisible(active);
	}

	SceneAnimatedMesh* Weapon::getScene() const
	{
		return m_scene;
	}


	void	Weapon::dump(std::ostream& os)	const
	{
		os << "Weapon {ID = " << Weapon::ID << ", WEAPON_NAME = \"" << Weapon::WEAPON_NAME << "\", MAX_AMMUNITION = " << Weapon::MAX_AMMUNITION
		   << ", DAMAGE = " << Weapon::DAMAGE << ", WEAPON_TYPE = " << Weapon::WEAPON_TYPE << ", ammunition = " << (static_cast<int>(m_ammunition) == -1 ? "none" : std::to_string(m_ammunition)) << ", sight = " << (m_sight == true ? "true" : "false") << ", scene = " << /*m_scene*/"Non implementer" << "}";
	}


	void	Weapon::serialize(RakNet::BitStream& out)	const
	{
		// TODO: implement serialization
	}

	void	Weapon::deserialize(RakNet::BitStream& in)
	{
		// TODO: implement deserialization
	}
};
