#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"

#define NUMBER_OF_INGREDIENTS		100		// Кол-во ингредиентов

#define MIN_PRICE					4.f		// Минимальная цена ингредиента
#define MAX_PRICE					135.f		// Максимальная цена ингредиента

class IngredientBuilder
{
public:

	// Конструктор по умолчанию
	IngredientBuilder();

	// Деструктор
	~IngredientBuilder();

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	void buildIngredient(int lastIndex, int& lastEffectIndex);

	// Добавить эффект
	void addEffect(int effectId);

	// Получить результат
	Ingredient* getResult();

private:

	// Экземпляр ингредиента
	Ingredient* ingredient;

	EffectsTable* effectsTable;

	// Выбрать имя эффекту
	string chooseIngredientName(int lastIndex);

	// Сгенерировать цену ингредиента
	int generatePrice();

#pragma region СЕТТЕРЫ

	// Задать имя
	void setName(string name);

	// Задать цену
	void setPrice(float price);



#pragma endregion СЕТТЕРЫ

	// Сбросить до начальных установок
	void reset();

	// Очизает память
	void clear();

	// Список имен ингредиентов
	static string listOfIngredientsNames[NUMBER_OF_INGREDIENTS];

	//// Список имен эффектов
	//static string listOfEffectsNames[55];
};

