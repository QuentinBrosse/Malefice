#pragma once

#include "AComponent.h"

namespace ecs
{
	class Spell : public AComponent
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
		Spell(const SpellType spellType);
		Spell(const Spell& cpy);
		~Spell() = default;

		const Spell::SpellType getSpellType()	const;

		void	dump()	const;


	private:
		const SpellType SPELL_TYPE;
	};
}
