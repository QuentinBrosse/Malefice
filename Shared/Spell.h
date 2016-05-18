#pragma once

#include <BitStream.h>
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
			SPELL_COUNT,
		};

		Spell();
		Spell(const int id, const std::string& name, const SpellType spellType, const int coolDown);
		Spell(const Spell& cpy);
		~Spell() = default;

		virtual void	init(const int id, const std::string& name, const SpellType spellType, const int coolDown);

		const Spell::SpellType	getSpellType()	const;
		void					setSpellType(const SpellType newSpellType);
		bool					isLock() const;
		void					lock();
		void					unlock();


		virtual void	dump(std::ostream& os)	const;

		virtual void	serialize(RakNet::BitStream& out, bool serializeType = true)	const;
		virtual void	deserialize(RakNet::BitStream& in);


	private:
		int			m_id;
		std::string	m_name;
		int			m_cooldown;
		SpellType	m_spellType;
		bool		m_isLock;
	};
}
