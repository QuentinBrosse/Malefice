#pragma once

#include "AComponent.h"

namespace ecs
{
	class Spell : public AComponent
	{
	public:
		typedef enum
		{
			NOTHING,
			BLIND,
			PARANOIA,
			CONFUSION,
			DEAF,
			PARKINSON,
			SLOW,
		} SpellType;

	public:
		Spell() = default;
		Spell(const SpellType spellType);
		Spell(const Spell& cpy);
		~Spell() = default;

		const Spell::SpellType getSpellType() const;

		void	dump() const;

	private:
		const SpellType SPELL_TYPE;
	};
}