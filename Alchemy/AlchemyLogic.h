#pragma once
//#include <string>
//#include <conio.h>
//#include <functional>
//#include "Formatting.h"
//#include "KeyBoard.h"
#include "Alchemist.h"
#include "IngredientsTable.h"
#include "PotionTable.h"
#include "EffectsTable.h"
#include "IngredientBuilder.h"
#include "PotionBuilder.h"
#include "ServiceFunctions.h"

//using namespace std;
//
//using std::placeholders::_1;

//// Координаты
//#define TITLE_Y_COORD			1		// Координаты Y курсора для печати названия программы
//#define Y_COORD_AFTER_TITLE		4		// Координата Y после названя программы
//
//// Коды клавиш
//#define VK_1					0x31	// Клавиша 1
//#define VK_2					0x32	// Клавиша 2
//#define VK_NUMPAD1				0x61	// Клавиша цифровой клавиатуры 1
//#define VK_NUMPAD2				0x62	// Клавиша цифровой клавиатуры 2
//#define VK_ESCAPE				0x1B	// Клавиша ESC
//#define VK_RETURN				0x0D	// Клавиша Enter

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

	void setPotionTable(PotionTable* potionTable);

	void setAlchemist(Alchemist* alchemist);

#pragma endregion СЕТТЕРЫ

#pragma region ГЕТТЕРЫ

	// Геттер для алхимика
	Alchemist* getAlchemist();

	// Геттер для таблицы эффектов
	EffectsTable* getEffectsTable();

	IngredientsTable* getIngredientsTable();

	PotionTable* getPotionTable();

#pragma endregion ГЕТТЕРЫ

	// Попробовать добавить опр. кол-во ингредиента из списка
	bool tryBuyIngredientFromList(int id, int number);

	bool tryAddNewIngredientToTable(string ingredientName);

	void checkPotion(Potion* potion);

	// Создть зелье
	Potion* createPotion(Ingredient* firstIngredient, Ingredient* secondIngredient);

	void sellIngredient(int ingredientId, int numberOfIngredient);

	void decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient);

	void eatIngredient(int ingredientId);

	//vector<int> findEqualEffects(int firstIngredientId, int secondIngredientId);

	//// Создать зелье и поместить его в таблицу
	//void addPotion(int effectId);

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

	//// Создать новый ингредиент
	//Ingredient* createNewIngredient(string ingredientName);
};

