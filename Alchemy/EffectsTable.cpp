#include "EffectsTable.h"
#include <iostream>

int EffectsTable::id = 0;

EffectsTable::EffectsTable()
{
	this->size = 0;
}

EffectsTable::~EffectsTable()
{
	clear();
}


void EffectsTable::addEffect(Effect* effect)
{
	//this->effects.push_back(effect);
	this->effectsWithId.emplace(++id, effect);

	++size;
}

void EffectsTable::print() const
{
	for (auto effect : effectsWithId)
	{
		cout << effect.first << ' ';
		effect.second->print();
		cout << endl;
	}
}

int EffectsTable::getSize()
{
	return this->size;
}

Effect* EffectsTable::getEffectByKey(int key)
{
	return this->effectsWithId[key];
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
