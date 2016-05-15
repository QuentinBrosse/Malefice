#pragma once

#include <map>
#include <utility>
#include <BitStream.h>
#include "Spell.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SpellManager : public AComponent
	{
	public:
		SpellManager();
		SpellManager(const Spell& defaultSpell);
		~SpellManager()	= default;

		Spell&	getCurrentSpell()	const;

		void	addSpell(const Spell& newSpell);
		void	changeToNextSpell();
		void	changeToPrecSpell();

		
		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		std::map<Spell::SpellType, Spell>				m_spells;
		std::map<Spell::SpellType, Spell>::iterator		m_currentSpell;
	};
}
