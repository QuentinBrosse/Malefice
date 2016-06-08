#include <iostream>
#include "Spell.h"
#include "NodePickable.h"
#include "TimeUtility.h"

namespace ecs
{
	const std::string	Spell::MEDIA_PATH = "spells/models/";

	Spell::Spell() : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(0), m_name("default"), m_cooldown(0), m_spellType(Spell::NOTHING), m_duration(0), m_fpsMetrics(0, 0, 0, 0, 0, 0, 0, 0, 0), m_externalMetrics(0, 0, 0, 0, 0, 0, 0, 0, 0), m_meshName(""), m_scene(nullptr), m_cooldownEndTime(0), m_effectEndTime(0)
	{
	}

	Spell::Spell(const int id, const std::string& name, const Spell::SpellType spellType, const size_t coolDown, const std::size_t duration, const Position& FPSMetrics, const Position& externalMetrics, const std::string& meshName) : AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(id), m_name(name), m_spellType(spellType), m_cooldown(coolDown), m_duration(m_cooldown), m_fpsMetrics(FPSMetrics), m_externalMetrics(externalMetrics), m_meshName(meshName), m_scene(nullptr), m_cooldownEndTime(0), m_effectEndTime(0)
	{
	}

	Spell::Spell(const Spell& cpy): AComponent("Spell", ecs::AComponent::ComponentType::SPELL),
		m_id(cpy.m_id), m_name(cpy.m_name), m_spellType(cpy.m_spellType), m_cooldown(cpy.m_cooldown), m_duration(cpy.m_duration), m_fpsMetrics(cpy.m_fpsMetrics), m_externalMetrics(cpy.m_externalMetrics), m_meshName(cpy.m_meshName), m_scene(nullptr), m_cooldownEndTime(cpy.m_cooldownEndTime), m_effectEndTime(cpy.m_effectEndTime)
	{
	}


	void	Spell::init(const int id, const std::string& name, const SpellType spellType, const std::size_t coolDown, const std::size_t duration, const Position& FPSMetrics, const Position& externalMetrics, const std::string& meshName)
	{
		m_id = id;
		m_name = name;
		m_spellType = spellType;
		m_cooldown = coolDown;
		m_duration = duration;
		m_fpsMetrics = FPSMetrics;
		m_externalMetrics = externalMetrics;
		m_meshName = meshName;
		m_scene = nullptr;
		m_cooldownEndTime = 0;
		m_effectEndTime = 0;
	}


	const Spell::SpellType	Spell::getSpellType() const
	{
		return m_spellType;
	}

	void Spell::setSpellType(const SpellType newSpellType)
	{
		m_spellType = newSpellType;
	}

	void Spell::setMeshName(const std::string& meshName)
	{
		m_meshName = meshName;
	}

	void Spell::setFPSMetrics(const Position& fpsMetrics)
	{
		m_fpsMetrics.affect(fpsMetrics);
	}

	void Spell::setExternalMetrics(const Position& externalMetrics)
	{
		m_externalMetrics.affect(externalMetrics);
	}

	void Spell::setCooldown(const std::size_t& cooldown)
	{
		m_cooldown = cooldown;
	}

	void Spell::setDuration(const std::size_t& duration)
	{
		m_duration = duration;
	}

	void Spell::setEffectEndTime(long long effectEndTime)
	{
		m_effectEndTime = effectEndTime;
	}

	void Spell::setCooldownEndTime(long long cooldownEndTime)
	{
		m_cooldownEndTime = cooldownEndTime;
	}

	bool Spell::isLock() const
	{
		return m_cooldownEndTime < utility::TimeUtility::getMsTime() && m_cooldownEndTime != 0;
	}

	Position Spell::getFPSMetrics() const
	{
		return m_fpsMetrics;
	}

	Position Spell::getExternalMetrics() const
	{
		return m_externalMetrics;
	}

	SceneAnimatedMesh* Spell::getScene() const
	{
		return m_scene;
	}

	const std::string& Spell::getMeshName() const
	{
		return m_meshName;
	}

	std::size_t Spell::getCooldown() const
	{
		return m_cooldown;
	}

	std::size_t Spell::getDuration() const
	{
		return m_duration;
	}

	long long Spell::getEffectEndTime() const
	{
		return m_effectEndTime;
	}

	long long Spell::getCooldownEndTime() const
	{
		return m_cooldownEndTime;
	}

	AComponent& Spell::affect(const AComponent& rhs)
	{
		const Spell&	spell = dynamic_cast<const Spell&>(rhs);

		m_id = spell.m_id;
		m_name = spell.m_name;
		m_cooldown = spell.m_cooldown;
		m_spellType = spell.m_spellType;
		m_duration = spell.m_duration;
		m_fpsMetrics = spell.m_fpsMetrics;
		m_externalMetrics = spell.m_externalMetrics;
		m_meshName = spell.m_meshName;
		m_cooldownEndTime = spell.m_cooldownEndTime;
		m_effectEndTime = spell.m_effectEndTime;
		return *this;
	}

	void Spell::createScene(irr::IrrlichtDevice* device, irr::scene::ISceneNode * parent, const bool active)
	{
		if (m_meshName == "") // DEBUG
			return;
		if (m_scene)
			delete m_scene;
		m_scene = new SceneAnimatedMesh(device, parent, "", MEDIA_PATH + m_meshName, nodePickable::NOT_PICKABLE, true, true, 0);

		m_scene->getScene()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		m_scene->getScene()->setName((MEDIA_PATH + m_meshName).c_str());

		this->setActivity(active);
	}

	void Spell::setActivity(const bool active)
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


	void	Spell::dump(std::ostream& os)	const
	{
		os << "Spell {ID = " << Spell::m_id << ", SPELL_NAME = \"" << Spell::m_name << "\", COOLDOWN = " << Spell::m_cooldown << ", spellType = " << m_spellType << ", isLock = " <<  "}";
	}


	void	Spell::serialize(RakNet::BitStream& out, bool serializeType)	const
	{
		AComponent::serialize(out, serializeType);
		out.Write(m_id);
		out.Write(RakNet::RakString(m_name.c_str()));
		out.Write(m_cooldown);
		out.Write(m_spellType);
		out.Write(m_duration);
		m_externalMetrics.serialize(out, false);
		m_fpsMetrics.serialize(out, false);
		out.Write(RakNet::RakString(m_meshName.c_str()));
		out.Write(m_cooldownEndTime);
		out.Write(m_effectEndTime);
	}

	void	Spell::deserialize(RakNet::BitStream& in)
	{
		RakNet::RakString	name;
		RakNet::RakString	meshName;

		AComponent::deserialize(in);
		in.Read(m_id);
		in.Read(name);
		in.Read(m_cooldown);
		in.Read(m_spellType);
		in.Read(m_duration);
		m_name = name.C_String();
		m_externalMetrics.deserialize(in);
		m_fpsMetrics.deserialize(in);
		in.Read(meshName);
		m_meshName = meshName.C_String();
		in.Read(m_cooldownEndTime);
		in.Read(m_effectEndTime);
	}

	AComponent * Spell::createCopy(const AComponent * rhs) const
	{
		const Spell*	spell = dynamic_cast<const Spell*>(rhs);

		return new Spell(*spell);
	}
}
