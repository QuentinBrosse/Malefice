#include <RakNetTypes.h>

#include "Weapon.h"
#include "NodePickable.h"
#include "RakNetUtility.h"
#include "IrrlichtUtility.h"

namespace ecs
{
	const std::string	Weapon::MEDIA_PATH = "weapons/models/";

	Weapon::Weapon() : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(0), m_weaponName(""), m_meshName(""), m_maxAmmunitions(0), m_maxAmmunitionsClip(0), m_damage(0), m_weaponType(WeaponType::DEFAULT), m_sight(false), m_ammunitions(0), m_ammunitionsClip(0), m_reloadTime(0), m_ammoPerShot(0), m_fireRate(0), m_distance(0), m_audioShot(""), m_audioReload(""), m_fpsMetrics(0, 0, 0, 0, 0, 0), m_fpsMetricsOffset(irr::core::vector3df(0.F, 0.F, 0.F)), m_fpsMetricsCoefOffset(0.F), m_externalMetrics(0, 0, 0, 0, 0, 0, 0, 0, 0), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int maxAmmunition, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const std::string& audioShot, const std::string& audioReload, const Position& fpsMetrics, const irr::core::vector3df fpsMetricsOffset, float fpsMetricsCoefOffset, const Position& externalMetrics, bool sight, unsigned int maxAmunitionsClip) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(id), m_weaponName(name), m_meshName(meshName), m_maxAmmunitions(maxAmmunition), m_maxAmmunitionsClip(maxAmunitionsClip), m_damage(damage), m_weaponType(weaponType), m_sight(sight), m_ammunitions(maxAmmunition - maxAmunitionsClip), m_ammunitionsClip(maxAmunitionsClip), m_reloadTime(reloadTime), m_ammoPerShot(ammoPerShot), m_fireRate(fireRate), m_distance(distance), m_audioShot(audioShot), m_audioReload(audioReload), m_fpsMetrics(fpsMetrics), m_fpsMetricsOffset(fpsMetricsOffset), m_fpsMetricsCoefOffset(fpsMetricsCoefOffset), m_externalMetrics(externalMetrics), m_scene(nullptr)
	{

	}

	Weapon::Weapon(const Weapon& cpy) : AComponent("Weapon", ecs::AComponent::ComponentType::WEAPON),
		m_id(cpy.getId()), m_weaponName(cpy.getName()), m_meshName(cpy.getMeshName()), m_maxAmmunitions(cpy.getMaxAmmunitions()), m_maxAmmunitionsClip(cpy.getMaxAmmunitionsClip()), m_damage(cpy.getDamage()), m_weaponType(cpy.getWeaponType()), m_sight(cpy.isSight()), m_ammunitions(cpy.getAmmunitions()), m_ammunitionsClip(cpy.getAmmunitionsClip()), m_reloadTime(cpy.getReloadTime()), m_ammoPerShot(cpy.getAmmoPerShot()), m_fireRate(cpy.getFireRate()), m_distance(cpy.getDistance()), m_audioShot(cpy.getAudioShot()), m_audioReload(cpy.getAudioReload()), m_fpsMetrics(cpy.m_fpsMetrics), m_fpsMetricsOffset(cpy.m_fpsMetricsOffset), m_fpsMetricsCoefOffset(cpy.m_fpsMetricsCoefOffset), m_externalMetrics(cpy.m_externalMetrics), m_scene(nullptr)
	{

	}

	Weapon::~Weapon()
	{

	}

	void	Weapon::init(const int id, const std::string& name, const std::string& meshName, WeaponType weaponType, float distance, float precision, unsigned int maxAmmunitions, float fireRate, unsigned int ammoPerShot, unsigned int damage, unsigned int reloadTime, const std::string& audioShot, const std::string& audioReload, const Position& fpsMetrix, const irr::core::vector3df fpsMetricsOffset, float fpsMetricsCoefOffset, const Position& externalMetrix, bool sight, unsigned int maxAmunitionsClip)
	{
		m_id = id;
		m_weaponName = name;
		m_meshName = meshName;
		m_maxAmmunitions = maxAmmunitions;
		m_maxAmmunitionsClip = maxAmunitionsClip;
		m_damage = damage;
		m_weaponType = weaponType;
		m_sight = sight;
		m_ammunitions = maxAmmunitions - maxAmunitionsClip;
		m_ammunitionsClip = maxAmunitionsClip;
		m_reloadTime = reloadTime;
		m_ammoPerShot = ammoPerShot;
		m_fireRate = fireRate;
		m_distance = distance;
		m_audioShot = audioShot;
		m_audioReload = audioReload;
		m_fpsMetrics = fpsMetrix;
		m_fpsMetricsOffset = fpsMetricsOffset;
		m_fpsMetricsCoefOffset = fpsMetricsCoefOffset;
		m_externalMetrics = externalMetrix;
		m_scene = nullptr;
		// TODO: implement constructor logic here
	}


	const bool Weapon::isSight() const
	{
		return m_sight;
	}

	const unsigned int	Weapon::getReloadTime() const
	{
		return m_reloadTime;
	}

	const unsigned int	Weapon::getAmmunitions() const
	{
		return m_ammunitions;
	}

	const unsigned int	Weapon::getMaxAmmunitions() const
	{
		return m_maxAmmunitions;
	}

	const unsigned int	Weapon::getAmmoPerShot() const
	{
		return m_ammoPerShot;
	}

	const unsigned int Weapon::getMaxAmmunitionsClip() const
	{
		return m_maxAmmunitionsClip;
	}

	const unsigned int Weapon::getAmmunitionsClip() const
	{
		return m_ammunitionsClip;
	}

	const float		Weapon::getFireRate() const
	{
		return m_fireRate;
	}

	const float		Weapon::getDistance() const
	{
		return m_distance;
	}

	const std::string&		Weapon::getAudioShot() const
	{
		return m_audioShot;
	}

	const std::string&		Weapon::getAudioReload() const
	{
		return m_audioReload;
	}

	Position	Weapon::getFPSMetrics() const
	{
		return m_fpsMetrics;
	}

	irr::core::vector3df	Weapon::getFPSMetricsOffset() const
	{
		return m_fpsMetricsOffset;
	}

	float		Weapon::getFPSMetricsCoefOffset() const
	{
		return  m_fpsMetricsCoefOffset;
	}

	Position	Weapon::getExternalMetrics() const
	{
		return m_externalMetrics;
	}

	const int	Weapon::getId() const
	{
		return m_id;
	}

	const	std::string & Weapon::getName() const
	{
		return m_weaponName;
	}

	const	std::string& Weapon::getMeshName() const
	{
		return m_meshName;
	}

	const int	Weapon::getDamage() const
	{
		return m_damage;
	}

	bool	Weapon::mustBeReloaded() const
	{
		return m_ammoPerShot > m_ammunitionsClip;
	}

	bool	Weapon::shoot()
	{
		if (!this->mustBeReloaded())
		{
			m_ammunitionsClip -= m_ammoPerShot;
			return true;
		}
		else
			this->reload();
		return false;
	}

	void	Weapon::reload()
	{
		if (m_ammunitions > 0)
		{
			int ammunitionLoadable = m_maxAmmunitionsClip - m_ammunitionsClip;
			if (m_ammunitions > ammunitionLoadable)
			{
				this->decAmmunition(ammunitionLoadable);
				m_ammunitionsClip += ammunitionLoadable;
			}
			else
			{
				m_ammunitionsClip += m_ammunitions;
				m_ammunitions = 0;
			}
		}
	}

	const	Weapon::WeaponType Weapon::getWeaponType() const
	{
		return m_weaponType;
	}

	void	Weapon::decAmmunition(int nbLoaded)
	{
		if (nbLoaded >= m_ammunitions)
			m_ammunitions = 0;
		else
			m_ammunitions -= nbLoaded;
	}

	void	Weapon::incAmmunition(int nbAmmunition)
	{
		m_ammunitions += nbAmmunition;
		if (m_ammunitions > m_maxAmmunitions)
			m_ammunitions = m_maxAmmunitions;
	}

	void	Weapon::createScene(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent, const bool active)
	{
		if (m_meshName == "")  //DEBUG
			return;
		if (m_scene)
			delete m_scene;
		m_scene = new SceneAnimatedMesh(device, parent, "", MEDIA_PATH + m_meshName, nodePickable::NOT_PICKABLE, true, true, 0);

		m_scene->getScene()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		m_scene->getScene()->setName((MEDIA_PATH + m_meshName).c_str());

		this->setActivity(active);
	}

	void	Weapon::setActivity(const bool active)
	{
		try
		{
			if (m_scene != nullptr)
				m_scene->getScene()->setVisible(active);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	SceneAnimatedMesh* Weapon::getScene() const
	{
		return m_scene;
	}

	void	Weapon::dump(std::ostream& os)	const
	{
		os << "Weapon {ID = " << Weapon::m_id << ", WEAPON_NAME = \"" << Weapon::m_weaponName << ", MESH_NAME = \"" << Weapon::m_meshName << "\", MAX_AMMUNITION = " << m_maxAmmunitions << "\", MAX_AMMUNITION_CLIP = " << m_maxAmmunitionsClip
			<< ", DAMAGE = " << Weapon::m_damage << ", WEAPON_TYPE = " << Weapon::m_weaponType << ", ammunition = " << (static_cast<int>(m_ammunitions) == -1 ? "none" : std::to_string(m_ammunitions)) << ", ammunition = " << (static_cast<int>(m_ammunitionsClip) == -1 ? "none" : std::to_string(m_ammunitionsClip)) << ", sight = " << (m_sight == true ? "true" : "false") << ", scene = " << /*m_scene*/"Non implementer" << "}";
	}

	AComponent * Weapon::createCopy(const AComponent * rhs) const
	{
		const Weapon* weapon = dynamic_cast<const Weapon*>(rhs);
		return new Weapon(*weapon);
	}

	AComponent& Weapon::affect(const AComponent& rhs)
	{
		const Weapon& weapon = dynamic_cast<const Weapon&>(rhs);

		m_id = weapon.m_id;
		m_weaponName = weapon.m_weaponName;
		m_maxAmmunitions = weapon.m_maxAmmunitions;
		m_maxAmmunitionsClip = weapon.m_maxAmmunitionsClip;
		m_meshName = weapon.m_meshName;
		m_damage = weapon.m_damage;
		m_weaponType = weapon.m_weaponType;
		m_sight = weapon.m_sight;
		m_ammunitions = weapon.m_ammunitions;
		m_ammunitionsClip = weapon.m_ammunitionsClip;
		m_reloadTime = weapon.m_reloadTime;
		m_ammoPerShot = weapon.m_ammoPerShot;
		m_fireRate = weapon.m_fireRate;
		m_distance = weapon.m_distance;
		//m_scene = nullptr;
		m_audioShot = weapon.m_audioShot;
		m_audioReload = weapon.m_audioReload;
		m_fpsMetrics = weapon.m_fpsMetrics;
		m_externalMetrics = weapon.m_externalMetrics;
		return *this;
	}

	void	Weapon::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_id);
		out.Write(RakNet::RakString(m_weaponName.c_str()));
		out.Write(m_maxAmmunitions);
		out.Write(m_maxAmmunitionsClip);
		out.Write(m_damage);
		out.Write(m_weaponType);
		out.Write(m_sight);
		out.Write(m_ammunitions);
		out.Write(m_ammunitionsClip);
		out.Write(m_reloadTime);
		out.Write(m_ammoPerShot);
		out.Write(m_fireRate);
		out.Write(m_distance);
		out.Write(RakNet::RakString(m_audioShot.c_str()));
		out.Write(RakNet::RakString(m_audioReload.c_str()));
		out.Write(RakNet::RakString(m_meshName.c_str()));
		m_externalMetrics.serialize(out, false);
		m_fpsMetrics.serialize(out, false);
	}

	void	Weapon::deserialize(RakNet::BitStream& in)
	{
		RakNet::RakString	meshName;
		RakNet::RakString	weaponName;
		RakNet::RakString	audioShot;
		RakNet::RakString	audioReload;

		AComponent::deserialize(in);
		in.Read(m_id);
		in.Read(weaponName);
		m_weaponName = weaponName.C_String();
		in.Read(m_maxAmmunitions);
		in.Read(m_maxAmmunitionsClip);
		in.Read(m_damage);
		in.Read(m_weaponType);
		in.Read(m_sight);
		in.Read(m_ammunitions);
		in.Read(m_ammunitionsClip);
		in.Read(m_reloadTime);
		in.Read(m_ammoPerShot);
		in.Read(m_fireRate);
		in.Read(m_distance);
		in.Read(audioShot);
		m_audioShot = audioShot.C_String();
		in.Read(audioReload);
		m_audioReload = audioReload.C_String();
		in.Read(meshName);
		m_meshName = meshName.C_String();
		m_externalMetrics.deserialize(in);
		m_fpsMetrics.deserialize(in);
	}

	void Weapon::deleteScene()
	{
		delete m_scene;
		m_scene = nullptr;
	}

};