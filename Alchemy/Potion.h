#pragma once
#include "Ingredient.h"
//#include "EffectsTable.h"

// Класс - зелье
class Potion
{
public:

	// Конструктор по умолчанию
	Potion();

	//// Конструктор с параметрами
	//Potion(Ingredient* ingredient1, Ingredient* ingredient2);

	void setEffectId(int id);

	void setPrice(int price);

	void setNumber(int number);

private:

	// id эффекта
	int effectId;

	// Цена
	int price;

	// Кол-во
	int number;

	//// Ищет есть ли у ингредиентов совпадения по эффектам
	//bool hasEffectsMatching(Ingredient* ingredient1, Ingredient* ingredient2);

};