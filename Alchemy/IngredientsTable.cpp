#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "Ингредиенты";
}

IngredientsTable::~IngredientsTable()
{
	clear();
}

void IngredientsTable::add(Ingredient* ingredient)
{
	this->ingredientsWithId.emplace(++id, ingredient);
}

void IngredientsTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

map<int, Ingredient*>::iterator IngredientsTable::getEndIterator()
{
	return --this->ingredientsWithId.end();
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

	map<int, Ingredient*>::iterator endIter = ++this->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// если имена совпадают, то возвращаем false
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

	map<int, Ingredient*>::iterator endIter = ++this->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// если имена совпадают, то возвращаем false
		if (i->second == ingredient)
		{
			return i->first;
		}
	}

	return 0;
}

void IngredientsTable::subscribe(IObserver* observer)
{
	this->observerList.push_back(observer);
}

void IngredientsTable::unsubscribe(IObserver* observer)
{
	// размер вектор
	int size = this->observerList.size();

	// итератор на первый элемент в векторе
	auto begin = this->observerList.cbegin();	

	for (int i = 0; i < size; ++i)
	{
		if (this->observerList[i] == observer)
		{
			this->observerList.erase(begin + i);
			break;
		}
	}
}

void IngredientsTable::notify(int id)
{
	for (auto observer : this->observerList)
	{
		observer->update(id);
	}
}

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
