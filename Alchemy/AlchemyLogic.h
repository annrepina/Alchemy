#pragma once
#include "Alchemist.h"
#include "IngredientsTable.h"
#include "PotionTable.h"
#include "EffectsTable.h"
#include "IngredientBuilder.h"
#include "PotionBuilder.h"
#include "ServiceFunctions.h"

#define ASCENDING_ORDER_OF_SORTING		true	// Порядок сортировки по возрастанию
#define DESCENDING_ORDER_OF_SORTING		false	// Порядок сортировки по убыванию

// Класс, представляющий логику зельеварения
class AlchemyLogic
{
public:

	// Конструктор по умолчанию
	AlchemyLogic();

#pragma region СЕТТЕРЫ

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Сеттер для таблицы ингредиентов
	void setIngredientsTable(IngredientsTable* ingredientsTable);

	// Сеттер для таблицы зельев
	void setPotionTable(PotionTable* potionTable);

	// Сеттер для алхимика
	void setAlchemist(Alchemist* alchemist);

#pragma endregion СЕТТЕРЫ

#pragma region ГЕТТЕРЫ

	// Геттер для алхимика
	Alchemist* getAlchemist();

	// Геттер для таблицы эффектов
	EffectsTable* getEffectsTable();

	// Геттер для таблицы ингредиентов
	IngredientsTable* getIngredientsTable();

	// Геттер для таблицы зельев
	PotionTable* getPotionTable();

#pragma endregion ГЕТТЕРЫ

	// Попробовать добавить опр. кол-во ингредиента из списка
	bool tryBuyIngredientFromList(int id, int number);

	// Попробовать добавить новый ингредиент в таблицу
	bool tryAddNewIngredientToTable(string ingredientName);

	// Проверить зелье, есть ли такое уже в таблице
	void checkPotion(Potion* potion, vector<Potion*> &potions);

	// Зелья одинаковые?
	bool isPotionsAreEqual(Potion* potion1, Potion* potion2);

	// Создть зелье
	Potion* createPotion(Ingredient* firstIngredient, Ingredient* secondIngredient);

	// Продать ингредиент
	void sellIngredient(int ingredientId, int numberOfIngredient);

	// Продать зелье
	void sellPotion(int potionId, int numberOfPotion);

	// Уменьшить кол-во ингредиента
	void decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient);

	// Уменьшить кол-во зелья
	void decreaseNumberOfPotion(int potionId, int numberOfPotion);

	// Съесть ингредиент
	void eatIngredient(int ingredientId);

	// Сортировка Когда данные строковые
	void sortStringData(vector<string>* tableData, int numberOfColumn, bool order, int size);

	// Сортировка Когда данные цифровые
	void sortDigitData(vector<string>* tableData, int numberOfColumn, bool order, int size);

private:

	// Алхимик (пользователь)
	Alchemist* alchemist;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Таблица ингредиентов
	IngredientsTable* ingredientsTable;

	// Таблица зелий
	PotionTable* potionTable;

	// Проверяет есть ли подобные названия ингредиентов уже в таблице
	bool hasSuchIngredientName(string ingredientName);

	// Имееет ли таблица такое зелье, если да то возвращает Id этого зелья
	int hasSuchPotion(Potion* potion);
};