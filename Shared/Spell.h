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
		};

	public:
		Spell();
		Spell(const SpellType spellType, const int coolDown);
		Spell(const Spell& cpy);
		~Spell() = default;

		const Spell::SpellType	getSpellType()	const;
		void					setSpellType(const SpellType newSpellType);
		bool					isLock() const;
		void					lock();
		void					unlock();

		void					dump()	const;


	private:
		SpellType				m_spellType;
		bool					m_isLock;
		const int				COOLDOWN;
	};
}
