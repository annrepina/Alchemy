#include "EffectsTable.h"

EffectsTable::EffectsTable()
{
}

EffectsTable::~EffectsTable()
{
	clear();
}


void EffectsTable::addEffect(Effect* effect)
{
	this->effects.push_back(effect);
}

void EffectsTable::clear()
{
	// ������� ������ � ������ ��������
	for (auto effect : effects)
	{
		if (nullptr != effect)
		{
			delete effect;
			effect = nullptr;
		}
	}
}
