#pragma once

#include "Ingredient.h"

class IngredientBuilder
{
public:

	// Конструктор по умолчанию
	IngredientBuilder();

	// Деструктор
	~IngredientBuilder();

	// Задать имя
	void setName(string name);

	// Задать цену
	void setPrice(float price);

	// Добавить эффект
	void addEffect(int effectId);

	// Получить результат
	Ingredient* getResult();

private:

	// Экземпляр ингредиента
	Ingredient* ingredient;

	// Сбросить до начальных установок
	void reset();

	// Очизает память
	void clear();

	// Список имен ингредиентов
	static string listOfIngredientsNames[100];

	// Список имен эффектов
	static string listOfEffectsNames[55];
};

