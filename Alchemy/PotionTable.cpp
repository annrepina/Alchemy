#include "PotionTable.h"
#include "ServiceFunctions.h"

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

void PotionTable::add(Potion* element, int id)
{
	this->potiontsWithId.emplace(id, element);

	notify(id, NEW_ELEMENT);
}

void PotionTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void PotionTable::setId(int id)
{
	this->id = id;
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

	// сначала уведомляем принтер об этом
	notify(potionId, NOT_NEW_ELEMENT);

	// если кол-во зелья равно 0, то удаляем его из таблицы
	if (potion->getNumber() == 0)
	{
		// удаляем из map данный элемент
		this->potiontsWithId.erase(potionId);

		// находим этот элемент в доступных элементах и удаляем
		int index = binarySearch(this->availableElements, potionId);

		auto beginIter = availableElements.begin();
		availableElements.erase(beginIter + index);

		// удаляем само зелье
		delete potion;
		potion = nullptr;

		// еще раз уведомляем принтер после окончательного удаления элемента, чтобы пересчитал данные по кол-ву строк
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

int PotionTable::getId()
{
	return this->id;
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
