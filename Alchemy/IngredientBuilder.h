#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"

#define NUMBER_OF_INGREDIENTS		100		// Кол-во ингредиентов

//#define MIN_PRICE					4		// Минимальная цена ингредиента
//#define MAX_PRICE					135		// Максимальная цена ингредиента

class IngredientBuilder
{
public:

	// Конструктор по умолчанию
	IngredientBuilder();

	// Деструктор
	~IngredientBuilder();

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

	// Заполнить список имен эффектов
	void fillEffectId();

	// Получить результат
	Ingredient* getResult();

private:

	// Экземпляр ингредиента
	Ingredient* ingredient;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Выбрать имя эффекту
	string chooseIngredientName(int lastIndex);

#pragma region СЕТТЕРЫ

	// Задать имя
	void setName(string name);

	// Задать цену
	void setPrice(int price);

#pragma endregion СЕТТЕРЫ

	// Сбросить до начальных установок
	void reset();

	// Очизает память
	void clear();

	// Список имен ингредиентов
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// Список имен эффектов
	vector<int> effectsId;

	// Кол-во ингредиентов
	int numberOfIngredients;
};

