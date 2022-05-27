#pragma once
#include "Ingredient.h"

// Таблица ингредиентов
class IngredientsTable
{
public:

	// Конструктор по умолчанию
	IngredientsTable();

	~IngredientsTable();

	void addIngredient(Ingredient* ingredient);

private:

	// Ингредиенты
	vector <Ingredient*> ingredients;

	void clear();

};

