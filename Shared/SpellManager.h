#pragma once

#include <map>
#include <utility>

#include "Spell.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SpellManager : public AComponent
	{
	public:
		SpellManager(const Spell& defaultSpell);
		~SpellManager()	= default;

		Spell&	getCurrentSpell()	const;

		void	addSpell(const Spell& newSpell);
		void	changeToNextSpell();
		void	changeToPrecSpell();

		void	dump()	const;

	private:
		std::map<Spell::SpellType, Spell>				m_spells;
		std::map<Spell::SpellType, Spell>::iterator		m_currentSpell;
	};
}
