#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>

#define NUMBER_OF_COLUMNS		6		// Кол-во колонок

// Таблица ингредиентов
class IngredientsTable : public Table
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
	void print() const override;

private:

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	void clear();

	void calculateLength() override;

	// Вернуть наибольший id
	int calculateMaxStrIdSize();

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize();

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumber();

};

