#include "PotionTable.h"

int PotionTable::id = 0;

PotionTable::PotionTable()
{
	this->title = "Зелья";
	this->effectsTable = nullptr;
}

PotionTable::~PotionTable()
{
	clear();
}

void PotionTable::add(Potion* potion)
{
	this->potiontsWithId.emplace(++id, potion);
}

void PotionTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

map<int, Potion*>::iterator PotionTable::getEndIterator()
{
	// возвращаем итератор на последний элемент
	return this->potiontsWithId.end();
}

map<int, Potion*>::iterator PotionTable::getStartIterator()
{
	// итератор на первый элемент
	return this->potiontsWithId.begin();
}

EffectsTable* PotionTable::getEffectsTable()
{
	return this->effectsTable;
}

Potion* PotionTable::getPotionById(int id)
{
	return this->potiontsWithId[id];
}

void PotionTable::clear()
{
	for (auto potion : potiontsWithId)
	{
		if (nullptr != potion.second)
		{
			delete potion.second;
			potion.second = nullptr;
		}
	}
}
