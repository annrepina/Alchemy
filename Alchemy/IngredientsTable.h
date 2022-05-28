#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>

#define NUMBER_OF_COLUMNS		6		// Кол-во колонок
#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)

#define MULTIPLIER				3		// Множитель для расчета длины таблицы

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


	// Расчитать длину таблицы
	void calculateLength();

private:

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();



	// Вернуть наибольший id
	int calculateMaxIdStrSize();

	// Вернуть самое длинное название ингредиента
	int calculateMaxNameSize();

	// Вернуть наибольшее кол-во ингредиентов
	int calculateMaxNumberStrSize();

	// Посчитать размеры максимальных имен эффектов
	int calculateMaxEffectNameSize();

	//// Хранит максимальные размеры имен эффектов
	//int effectsNameSizes[NUMBER_OF_EFFECTS];

};

