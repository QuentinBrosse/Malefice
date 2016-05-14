#pragma once

#include <map>
#include <utility>

#include "WeaponManager.h"
#include "Spell.h"
#include "Export.h"

namespace ecs
{
	class MALEFICE_DLL_EXPORT SpellManager : public AComponent
	{
	public:
		SpellManager(const Spell& defaultSpell);
		~SpellManager()	= default;

		Spell&	getCurrentSpell()				const;
		bool	weaponsIsCurrent()				const;

		void	changeCurrentManager();

		void	addSpell(const Spell& newSpell);
		
		void	changeToNextSpell();
		void	changeToPrecSpell();


		Weapon&	getCurrentWeapon()				const;

		void	changeToNextWeapon();
		void	changeToPrecWeapon();
		
		virtual void	dump(std::ostream& os)	const;


	private:
		std::map<Spell::SpellType, Spell>				m_spells;
		std::map<Spell::SpellType, Spell>::iterator		m_currentSpell;
		WeaponManager									m_weaponManager;
		bool											m_weaponsIsCurrent;
	};
}
