#include "Weapon.h"
#include "NodePickable.h"
#include "RakNetUtility.h"

namespace ecs
{
	Weapon::Weapon() : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(0), m_weaponName(""), m_maxAmmunition(0), m_damage(0), m_weaponType(WeaponType::DEFAULT), m_sight(false), m_ammunition(0), m_reloadTime(0), m_ammoPerShot(0), m_fireRate(0), m_distance(0), m_fpsMetricsPosition(0, 0, 0), m_fpsMetricsRotation(0, 0, 0), m_fpsMetricsScale(0, 0, 0), m_externalMetricsPosition(0, 0, 0), m_externalMetricsRotation(0, 0, 0), m_externalMetricsScale(0, 0, 0), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const int id, const std::string& name, WeaponType weaponType, float distance, float precision, unsigned int ammunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, irr::core::vector3df	fpsMetricsPosition, irr::core::vector3df fpsMetricsRotation, irr::core::vector3df fpsMetricsScale, irr::core::vector3df	externalMetricsPosition, irr::core::vector3df externalMetricsRotation, irr::core::vector3df	externalMetricsScale, bool sight) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(id), m_weaponName(name), m_maxAmmunition(ammunition), m_damage(damage), m_weaponType(weaponType), m_sight(sight), m_ammunition(ammunition), m_reloadTime(reloadTime), m_ammoPerShot(ammoPerShot), m_fireRate(fireRate), m_distance(distance), m_fpsMetricsPosition(fpsMetricsPosition), m_fpsMetricsRotation(fpsMetricsRotation), m_fpsMetricsScale(fpsMetricsScale), m_externalMetricsPosition(externalMetricsPosition), m_externalMetricsRotation(externalMetricsRotation), m_externalMetricsScale(externalMetricsScale), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(cpy.getId()), m_weaponName(cpy.getName()), m_maxAmmunition(cpy.getMaxAmmunitions()), m_damage(cpy.getDamage()), m_weaponType(cpy.getWeaponType()), m_sight(cpy.isSight()), m_ammunition(cpy.getAmmunitions()), m_reloadTime(cpy.getReloadTime()), m_ammoPerShot(cpy.getAmmoPerShot()), m_fireRate(cpy.getFireRate()), m_distance(cpy.getDistance()), m_fpsMetricsPosition(cpy.getFPSMetricsPosition()), m_fpsMetricsRotation(cpy.getFPSMetricsRotation()), m_fpsMetricsScale(cpy.getFPSMetricsScale()), m_externalMetricsPosition(cpy.getExternalMetricsPosition()), m_externalMetricsRotation(cpy.getExternalMetricsRotation()), m_externalMetricsScale(cpy.getExternalMetricsScale()), m_scene(nullptr)
	{

	}


	void	Weapon::init()
	{
		// TODO: implement constructor logic here
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
		return m_maxAmmunition;
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
		return m_id;
	}

	const std::string & Weapon::getName() const
	{
		return m_weaponName;
	}

	const int		Weapon::getDamage() const
	{
		return m_damage;
	}

	void Weapon::shot()
	{
		this->decAmmunition(m_ammoPerShot);
	}

	void Weapon::reload()
	{
	}

	const Weapon::WeaponType Weapon::getWeaponType() const
	{
		return m_weaponType;
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
		if (m_ammunition > m_maxAmmunition)
			m_ammunition = m_maxAmmunition;
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
		os << "Weapon {ID = " << Weapon::m_id << ", WEAPON_NAME = \"" << Weapon::m_weaponName << "\", MAX_AMMUNITION = " << Weapon::m_maxAmmunition
		   << ", DAMAGE = " << Weapon::m_damage << ", WEAPON_TYPE = " << Weapon::m_weaponType << ", ammunition = " << (static_cast<int>(m_ammunition) == -1 ? "none" : std::to_string(m_ammunition)) << ", sight = " << (m_sight == true ? "true" : "false") << ", scene = " << /*m_scene*/"Non implementer" << "}";
	}


	void	Weapon::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_id);
		out.Write(m_weaponName);
		out.Write(m_maxAmmunition);
		out.Write(m_damage);
		out.Write(m_weaponType);
		out.Write(m_sight);
		out.Write(m_ammunition);
		out.Write(m_reloadTime);
		out.Write(m_ammoPerShot);
		out.Write(m_fireRate);
		out.Write(m_distance);
		m_scene->serialize(out, false);
		RakNetUtility::serializeVector(out, m_fpsMetricsPosition);
		RakNetUtility::serializeVector(out, m_fpsMetricsRotation);
		RakNetUtility::serializeVector(out, m_fpsMetricsScale);
		RakNetUtility::serializeVector(out, m_externalMetricsPosition);
		RakNetUtility::serializeVector(out, m_externalMetricsRotation);
		RakNetUtility::serializeVector(out, m_externalMetricsScale);
	}

	void	Weapon::deserialize(RakNet::BitStream& in)
	{
		AComponent::deserialize(in);
		in.Read(m_id);
		in.Read(m_weaponName);
		in.Read(m_maxAmmunition);
		in.Read(m_damage);
		in.Read(m_weaponType);
		in.Read(m_sight);
		in.Read(m_ammunition);
		in.Read(m_reloadTime);
		in.Read(m_ammoPerShot);
		in.Read(m_fireRate);
		in.Read(m_distance);
		m_scene->deserialize(in);
		RakNetUtility::deserializeVector(in, m_fpsMetricsPosition);
		RakNetUtility::deserializeVector(in, m_fpsMetricsRotation);
		RakNetUtility::deserializeVector(in, m_fpsMetricsScale);
		RakNetUtility::deserializeVector(in, m_externalMetricsPosition);
		RakNetUtility::deserializeVector(in, m_externalMetricsRotation);
		RakNetUtility::deserializeVector(in, m_externalMetricsScale);
	}
};
