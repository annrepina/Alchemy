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

	notify(id);
}

void PotionTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

int PotionTable::hasSuchPotion(Potion* potion)
{
	// начальный индекс
	bool key = -1;

	auto beginIter = getStartIterator();
	auto endIter = getEndIterator();

	int effectId = potion->getEffectId();
	int price = potion->getPrice();
	int power = potion->getPower();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// если совпадают основные показатели
		if (effectId == i->second->getEffectId() && price == i->second->getPrice() && power == i->second->getPower())
		{
			key = i->first;

			break;
		}
	}

	return key;
}

void PotionTable::update(int id)
{
}

void PotionTable::update(int id, int previousNumber)
{
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

Potion* PotionTable::getSuchPotion(Potion* potion)
{
	auto beginIter = getStartIterator();
	auto endIter = getEndIterator();

	int effectId = potion->getEffectId();
	int price = potion->getPrice();
	int power = potion->getPower();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// если совпадают основные показатели
		if (effectId == i->second->getEffectId() && price == i->second->getPrice() && power == i->second->getPower())
		{
			hasPotion = true;

			break;
		}
	}

	return nullptr;
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
