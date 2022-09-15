#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Builder.h"

#define NUMBER_OF_INGREDIENTS		100		// Кол-во ингредиентов

// Строитель ингредиентов
class IngredientBuilder : public Builder<Ingredient>
{
public:

	// Конструктор по умолчанию
	IngredientBuilder();

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Получить размер таблицы 
	int getEffectsTableSize();

	// Геттер для таблицы эффектов
	EffectsTable* getEffectsTable();

	// Создать ингредиент
	void buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex);

	// Создать ингредиент по имени
	void buildIngredient(string ingredientName, EffectsTable* effectsTable);

	// Добавить эффект
	void addEffect(int effectId);

	// Заполнить список id эффектов
	void fillEffectId();

#pragma region СЕТТЕРЫ

	// Задать имя
	void setName(string name);

	// Задать имя
	void setNameFromListRandomly(int lastIngredientNameIndex);

	// Задать цену
	void setPrice(int price);

	// Задать цену рандомно
	void setPriceRandomly();

	// Задает ингредиенту эффекты
	void setEffects(int& lastEffectIndex);

	// Задает ингредиенты рандомно без привязки к конкретному индексу
	void setEffectsRandomly();

#pragma endregion СЕТТЕРЫ

private:

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Выбрать имя эффекту
	string chooseIngredientName(int lastIndex);

	// Список имен ингредиентов
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	// Список id эффектов
	vector<int> effectsId;
};