#include "EffectsTable.h"

EffectsTable::EffectsTable()
{
}

void EffectsTable::addEffect(Effect* effect)
{
	this->effects.push_back(effect);
}
