#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
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

void IngredientsTable::print()
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
