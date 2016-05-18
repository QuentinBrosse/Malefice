#pragma once

#include <map>
#include <utility>
#include <BitStream.h>
#include "WeaponManager.h"
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

		void	init(const Spell& defaultSpell);

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

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		std::map<Spell::SpellType, Spell>			m_spells;
		std::map<Spell::SpellType, Spell>::iterator	m_currentSpell;
		WeaponManager								m_weaponManager;
		bool										m_weaponsIsCurrent;
	};
}
