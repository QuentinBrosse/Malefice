#include "SpellCreator.h"

SpellCreator::SpellCreator()
{
	m_configurator = &SpellsConfiguration::getInstance();
	m_spells = m_configurator->getSpells();
}

ecs::Spell SpellCreator::create(const ecs::Spell::SpellType spellType)
{
	return m_spells[spellType];
}
