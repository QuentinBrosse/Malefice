#pragma once

#include <BitStream.h>
#include "AComponent.h"
#include "Export.h"
#include "Position.h"
#include "SceneAnimatedMesh.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT Spell : public AComponent
	{
	public:
		enum SpellType
		{
			NOTHING,
			BLIND,
			PARANOIA,
			CONFUSION,
			DEAF,
			PARKINSON,
			SLOW,
			SPELL_COUNT,
		};

		Spell();
		Spell(const int id, const std::string& name, const SpellType spellType, const std::size_t coolDown, const std::size_t duration, const Position& FPSMetrics, const Position& externalMetrics, const std::string& meshName);
		Spell(const Spell& cpy);
		~Spell() = default;

		virtual void			init(const int id, const std::string& name, const SpellType spellType, const std::size_t coolDown, const std::size_t duration, const Position& FPSMetrics, const Position& externalMetrics, const std::string& meshName);

		const Spell::SpellType	getSpellType()			const;
		bool					isLock()				const;
		Position				getFPSMetrics()			const;
		Position				getExternalMetrics()	const;
		SceneAnimatedMesh*		getScene()				const;
		const std::string&		getMeshName()			const;
		std::size_t				getCooldown()			const;
		std::size_t				getDuration()			const;

		void					setSpellType(const SpellType newSpellType);
		void					setMeshName(const std::string& meshName);
		void					setFPSMetrics(const Position& fpsMetrics);
		void					setExternalMetrics(const Position& externalMetrics);
		void					setCooldown(const std::size_t& cooldown);
		void					setDuration(const std::size_t& duration);
		void					lock();
		void					unlock();

		virtual AComponent&		affect(const AComponent& rhs);

		void					createScene(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent, const bool active);

		void					setActivity(const bool active);

		virtual void			dump(std::ostream& os)	const;

		virtual void			serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void			deserialize(RakNet::BitStream& in);

		virtual	AComponent*		createCopy(const AComponent* rhs) const;

	private:
		static const std::string	MEDIA_PATH;

		int					m_id;
		std::string			m_name;
		SpellType			m_spellType;

		std::size_t			m_cooldown;
		std::size_t			m_duration;

		bool				m_isLock;

		Position			m_fpsMetrics;
		Position			m_externalMetrics;

		SceneAnimatedMesh*	m_scene;
		std::string			m_meshName;
	};
}
