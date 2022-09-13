#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"
#include "ServiceFunctions.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "�����������";
}

IngredientsTable::~IngredientsTable()
{
	clear();
}

void IngredientsTable::add(Ingredient* ingredient)
{
	this->ingredientsWithId.emplace(++id, ingredient);

	ingredient->subscribe(this);
}

void IngredientsTable::add(Ingredient* element, int id)
{
	this->ingredientsWithId.emplace(id, element);

	element->subscribe(this);
}

void IngredientsTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void IngredientsTable::setId(int id)
{
	this->id = id;
}

void IngredientsTable::update(int id, bool isNewElement)
{
	notify(id, isNewElement);
}

void IngredientsTable::update(int id, int previousNumber)
{
}

void IngredientsTable::update()
{
}

map<int, Ingredient*>::iterator IngredientsTable::getEndIterator()
{
	return this->ingredientsWithId.end();
}

map<int, Ingredient*>::iterator IngredientsTable::getStartIterator()
{
	return this->ingredientsWithId.begin();
}

EffectsTable* IngredientsTable::getEffectsTable()
{
	return this->effectsTable;
}

Ingredient* IngredientsTable::getIngredientById(int id)
{
	return this->ingredientsWithId[id];
}

Ingredient* IngredientsTable::getIngredientByName(string name)
{
	map<int, Ingredient*>::iterator startIter = this->getStartIterator();

	map<int, Ingredient*>::iterator endIter = this->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ���� ����� ���������, �� ���������� false
		if (i->second->getName() == name)
		{
			return i->second;
		}
	}

	return nullptr;
}

int IngredientsTable::getIdByIngredient(Ingredient* ingredient)
{
	map<int, Ingredient*>::iterator startIter = this->getStartIterator();

	map<int, Ingredient*>::iterator endIter = this->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ���� ����� ���������, �� ���������� false
		if (i->second == ingredient)
		{
			return i->first;
		}
	}

	return 0;
}

int IngredientsTable::getId()
{
	return this->id;
}

void IngredientsTable::decreaseNumberOfIngredient(int ingredientId, int number)
{
	int previousNumber = getIngredientById(ingredientId)->getNumber();

	// �������� ���������� � ��������� ��� ���-��
	getIngredientById(ingredientId)->decreaseNumber(number);

	// ���� ���-�� ����������� ����� ����, �� ������� ���� ����������
	if (getIngredientById(ingredientId)->getNumber() == 0)
	{
		int index = binarySearch(availableElements, ingredientId);

		auto beginIter = availableElements.begin();

		availableElements.erase(beginIter + index);
	}

	// ���������� ����
	notify(ingredientId, previousNumber);
}

//void IngredientsTable::subscribe(IObserver* observer)
//{
//	this->observerList.push_back(observer);
//}

//void IngredientsTable::unsubscribe(IObserver* observer)
//{
//	// ������ ������
//	int size = this->observerList.size();
//
//	// �������� �� ������ ������� � �������
//	auto begin = this->observerList.cbegin();	
//
//	for (int i = 0; i < size; ++i)
//	{
//		if (this->observerList[i] == observer)
//		{
//			this->observerList.erase(begin + i);
//			break;
//		}
//	}
//}

//void IngredientsTable::notify(int id)
//{
//	for (auto observer : this->observerList)
//	{
//		observer->update(id);
//	}
//}

void IngredientsTable::clear()
{
	for (auto ingredient : ingredientsWithId)
	{
		if (nullptr != ingredient.second)
		{
			delete ingredient.second;
			ingredient.second = nullptr;
		}
	}
}
