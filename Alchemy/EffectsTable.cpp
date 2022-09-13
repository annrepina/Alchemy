#include "EffectsTable.h"
#include <iostream>

int EffectsTable::id = 0;

EffectsTable::EffectsTable()
{
	this->size = 0;
	this->title = "Ёффекты";
}

EffectsTable::~EffectsTable()
{
	clear();
}

void EffectsTable::add(Effect* effect)
{
	this->effectsWithId.emplace(++id, effect);

	++size;
}

void EffectsTable::add(Effect* effect, int id)
{
	this->effectsWithId.emplace(id, effect);

	++size;
}

void EffectsTable::print()
{
	for (auto effect : effectsWithId)
	{
		cout << effect.first << ' ';
		effect.second->print();
		cout << endl;
	}
}

int EffectsTable::getId()
{
	return this->id;
}

int EffectsTable::getSize()
{
	return this->size;
}

Effect* EffectsTable::getEffectByKey(int key)
{
	return this->effectsWithId[key];
}

map<int, Effect*>::iterator EffectsTable::getStartIterator()
{
	return this->effectsWithId.begin();
}

map<int, Effect*>::iterator EffectsTable::getEndIterator()
{
	return this->effectsWithId.end();
}

void EffectsTable::setId(int id)
{
	this->id = id;
}

void EffectsTable::clear()
{
	// ќчищаем пам€ть в каждом элементе
	for (auto effect : this->effectsWithId)
	{
		if (nullptr != effect.second)
		{
			delete effect.second;
			effect.second = nullptr;
		}
	}
}
