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
		SpellManager(const SpellManager& cpy);
		SpellManager(const Spell& defaultSpell, const int cooldown);
		~SpellManager()	= default;

		void	init(const Spell& defaultSpell, const int cooldown);

		Spell&		getCurrentSpell()		const;
		bool		weaponsIsCurrent()		const;
		long long	getCooldownEndTime()	const;
		int			getCooldown()			const;
		bool		isLock()				const;

		void		setCooldownEndTime(const long long cooldownEndTime);

		void	changeCurrentManager();

		void	addSpell(const Spell& newSpell);
		
		void	changeToNextSpell();
		void	changeToPrecSpell();

		bool								hasCurrentWeapon()	const;
		Weapon&								getCurrentWeapon()	const;
		std::map<Spell::SpellType, Spell>&	getSpells();

		void	changeToNextWeapon();
		void	changeToPrecWeapon();

		void	createFPSScene(irr::IrrlichtDevice* device, irr::scene::ISceneNode* parent);

		void	createExternalScene(irr::IrrlichtDevice * device, irr::scene::ISceneNode * parent);
		
		virtual	AComponent&	affect(const AComponent& rhs);

		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);

		virtual AComponent*	createCopy(const AComponent* rhs) const;

	private:
		std::map<Spell::SpellType, Spell>			m_spells;
		std::map<Spell::SpellType, Spell>::iterator	m_currentSpell;
		WeaponManager								m_weaponManager;
		bool										m_weaponsIsCurrent;
		int											m_cooldown;
		long long									m_cooldownEndTime;
	};
}
