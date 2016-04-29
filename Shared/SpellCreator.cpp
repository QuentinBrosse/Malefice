#include "SpellCreator.h"

SpellCreator::SpellCreator(const std::string& XMLFilename):
	XML_FILENAME(XMLFilename)
{
}

ecs::Spell SpellCreator::create(const ecs::Spell::SpellType spellType)
{
	return m_spells[spellType];
}

void SpellCreator::loadSpells()
{
}
