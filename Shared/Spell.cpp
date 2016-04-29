#include "Spell.h"

namespace ecs
{

	Spell::Spell(const Spell::SpellType spellType) : AComponent("Spell", SPELL),
		SPELL_TYPE(spellType)
	{

	}

	Spell::Spell(const Spell & cpy): AComponent("Spell", SPELL),
		SPELL_TYPE(cpy.SPELL_TYPE)
	{
	}

	const Spell::SpellType	Spell::getSpellType() const
	{
		return SPELL_TYPE;
	}

	void Spell::dump() const
	{
		std::cout << "[" << NAME << ": " << SPELL_TYPE << "]" << std::endl;
	}
}