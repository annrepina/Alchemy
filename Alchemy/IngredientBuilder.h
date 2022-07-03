#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Builder.h"

#define NUMBER_OF_INGREDIENTS		100		// Кол-во ингредиентов

//#define MIN_PRICE					4		// Минимальная цена ингредиента
//#define MAX_PRICE					135		// Максимальная цена ингредиента

class IngredientBuilder : public Builder<Ingredient>
{
public:

	// Конструктор по умолчанию
	IngredientBuilder();

	//// Деструктор
	//~IngredientBuilder();

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Получить размер таблицы 
	int getEffectsTableSize();

	// Геттер для таблицы эффектов
	EffectsTable* getEffectsTable();

	// Создать ингредиент
	void buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex);

	// Добавить эффект
	void addEffect(int effectId);

	// Заполнить список id эффектов
	void fillEffectId();

#pragma region СЕТТЕРЫ

	// Задать имя
	void setName(string name);

	// Задать цену
	void setPrice(int price);

#pragma endregion СЕТТЕРЫ

private:

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Выбрать имя эффекту
	string chooseIngredientName(int lastIndex);

	//// Сбросить до начальных установок
	//void reset();

	//// Очизает память
	//void clear();

	// Список имен ингредиентов
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// Список id эффектов
	vector<int> effectsId;
};

