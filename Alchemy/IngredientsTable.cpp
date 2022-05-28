#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "Существующие ингредиенты";
	this->numberOfColumns = NUMBER_OF_COLUMNS;
}

IngredientsTable::~IngredientsTable()
{
}

void IngredientsTable::addIngredient(Ingredient* ingredient)
{
	this->ingredientsWithId.emplace(++id, ingredient);
}

void IngredientsTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void IngredientsTable::print() const
{
	//int size = this->ingredientsWithId.size();

	//for (int i = 0; i < size; ++i)
	//{
	//	cout << this->ingredientsWithId[i] << ' ';


	//}



	for (auto ingredient : this->ingredientsWithId)
	{
		cout << ingredient.first << ' ';
		ingredient.second->print();

		// печатаем эффекты
		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
		{
			this->effectsTable->getEffectByKey(ingredient.second->getEffectId(i))->print();
			cout << ' ';
		}

		cout << endl;
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

void IngredientsTable::calculateLength()
{
	//this->length = this->numberOfColumns + 1;

	int length;

	// Длина наибольшего id
	length = calculateMaxIdStrSize();

	// Длина наибольшего имени ингредиента
	length += calculateMaxNameSize();

	// Длина наибольшей цены
	length += to_string(MAX_PRICE).size();

	// Длина наибольшего кол-ва
	length += calculateMaxNumberStrSize();

	//length +=
}

int IngredientsTable::calculateMaxIdStrSize()
{
	// Последний id
	int maxId;

	// Последний id в виде строки
	string strMaxId;

	// Размер строки последнего id 
	int maxStrIdSize;

	//map<int, Ingredient*>::reverse_iterator rit;

	//rit = this->ingredientsWithId.rbegin();

	//biggest = rit->first;

	maxId = (--this->ingredientsWithId.end())->first;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTable::calculateMaxNameSize()
{
	// Присваеваем самому длинному размеру размер имени первого ингредиента в map
	int maxNameSize = this->ingredientsWithId.begin()->second->getName().size();

	// Для каждого ингредиента
	for (auto ingredient : this->ingredientsWithId)
	{
		// Присваиваем размер имени текущего элемента
		int size = ingredient.second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTable::calculateMaxNumberStrSize()
{
	// мах кол-во ингредиентов
	int maxNumberSize = this->ingredientsWithId.begin()->second->getNumber();

	// мах кол-во ингредиентов в виде строки
	string strMaxNumber;

	// Размер строки мах кол-ва ингредиентов 
	int strMaxNumberSize;

	// Для каждого ингредиента
	for (auto ingredient : this->ingredientsWithId)
	{
		// Присваиваем кол-вj текущего элемента
		int number = ingredient.second->getNumber();

		if (maxNumberSize < number)
			maxNumberSize = number;
	}

	strMaxNumber = to_string(maxNumberSize);

	strMaxNumberSize = strMaxNumber.size();

	return strMaxNumberSize;
}

void IngredientsTable::calculateMaxEffectsNamesSize()
{
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{

	}
}
