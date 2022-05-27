#include "IngredientsTable.h"

IngredientsTable::IngredientsTable()
{
}

IngredientsTable::~IngredientsTable()
{
}

void IngredientsTable::addIngredient(Ingredient* ingredient)
{
	this->ingredients.push_back(ingredient);
}

void IngredientsTable::clear()
{
	for (auto ingredient : ingredients)
	{
		if (nullptr != ingredient)
		{
			delete ingredient;
			ingredient = nullptr;
		}
	}
}
