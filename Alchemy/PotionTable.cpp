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

	notify(id, NEW_ELEMENT);
}

void PotionTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

int PotionTable::hasSuchPotion(Potion* potion)
{
	// начальный индекс
	int key = -1;

	auto mapp = this->potiontsWithId;

	auto beginIter = getStartIterator();
	auto endIter = getEndIterator();



	//Potion* potion1 = beginIter->second;

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

void PotionTable::update(int id, bool isNewElement)
{
}

void PotionTable::update(int id, int previousNumber)
{
}

void PotionTable::update()
{
}

void PotionTable::decreaseNumberOfPotion(int potionId, int number)
{
	Potion* potion = getPotionById(potionId);

	// Получаем зелье и уменьшаем его кол-во
	potion->decreaseNumber(number);

	// если кол-во зелья равно 0, то удаляем его из таблицы
	if (potion->getNumber() == 0)
	{
		// сначала уведомляем принтер об этом
		notify(potionId, NOT_NEW_ELEMENT);

		// удаляем из map данный элемент
		this->potiontsWithId.erase(potionId);

		// удаляем само зелье
		delete potion;
		potion = nullptr;

		// еще раз уведомляем принтер после окончательного удаления элемента
		notify();
	}
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

int PotionTable::getSize()
{
	return this->potiontsWithId.size();
}

//Potion* PotionTable::getSuchPotion(Potion* potion)
//{
//	Potion* potion = nullptr;
//
//	auto beginIter = getStartIterator();
//	auto endIter = getEndIterator();
//
//	int effectId = potion->getEffectId();
//	int price = potion->getPrice();
//	int power = potion->getPower();
//
//	for (auto i = beginIter; i != endIter; ++i)
//	{
//		// если совпадают основные показатели
//		if (effectId == i->second->getEffectId() && price == i->second->getPrice() && power == i->second->getPower())
//		{
//			potion = i->second;
//
//			break;
//		}
//	}
//
//	return potion;
//}

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
