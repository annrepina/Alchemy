#include "EffectsTable.h"
#include <iostream>

int EffectsTable::id = 0;

EffectsTable::EffectsTable()
{
}

EffectsTable::~EffectsTable()
{
	clear();
}


void EffectsTable::addEffect(Effect* effect)
{
	//this->effects.push_back(effect);
	this->effectsWithId.emplace(++id, effect);
}

void EffectsTable::print()
{
	for (auto effect : effectsWithId)
	{
		cout << effect.first << "\t";
		effect.second->print();
		cout << endl;
	}
}

void EffectsTable::clear()
{
	// Очищаем память в каждом элементе
	for (auto effect : this->effectsWithId)
	{
		if (nullptr != effect.second)
		{
			delete effect.second;
			effect.second = nullptr;
		}
	}
}
