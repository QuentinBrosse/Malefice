#pragma once

#include "Spell.h"

namespace ecs
{
	class SpellManager : public AComponent
	{
	public:
		SpellManager(const Spell& defaultSpell);
		~SpellManager() = default;

		Spell&	getCurrentSpell() const;

		void	addSpell(const Spell& newSpell);
		void	changeToNextSpell();
		void	changeToPrecSpell();

		void	dump() const;

	private:
		std::map<Spell::SpellType, Spell>				m_spells;
		std::map<Spell::SpellType, Spell>::iterator		m_currentSpell;
	};
}