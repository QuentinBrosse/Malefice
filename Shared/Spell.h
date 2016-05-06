#pragma once

#include "AComponent.h"
#include "Export.h"

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

	public:
		Spell();
		Spell(const int id, const std::string& name, const SpellType spellType, const int coolDown);
		Spell(const Spell& cpy);
		~Spell() = default;

		const Spell::SpellType	getSpellType()	const;
		void					setSpellType(const SpellType newSpellType);
		bool					isLock() const;
		void					lock();
		void					unlock();

		void					dump()	const;


	private:
		const int				ID;
		const std::string		SPELL_NAME;
		const int				COOLDOWN;
		SpellType				m_spellType;
		bool					m_isLock;
	};
}
