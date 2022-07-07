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

#pragma region Сеттеры

	void setEffectId(int id);

	void setPrice(int price);

	void setNumber(int number);

	void setPower(int power);

#pragma endregion Сеттеры

#pragma region Геттеры

	int getNumber();

	int getEffectId();

	int getPower();

	int getPrice();

#pragma endregion Геттеры

private:

	// id эффекта
	int effectId;

	// Цена
	int price;

	// Кол-во
	int number;

	// Мощность зелья, которая зависит от уровня алхимика
	int power;

};