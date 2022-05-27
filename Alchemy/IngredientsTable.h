#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include <map>

// Таблица ингредиентов
class IngredientsTable
{
public:

	// Конструктор по умолчанию
	IngredientsTable();

	~IngredientsTable();

	// Добавить ингредиент в таблицу
	void addIngredient(Ingredient* ingredient);

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Печать таблицы
	void print();

private:

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	void clear();

};

