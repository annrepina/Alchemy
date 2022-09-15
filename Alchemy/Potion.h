#pragma once
#include "Ingredient.h"

// Класс - зелье
class Potion
{
public:

	// Конструктор по умолчанию
	Potion();

	// Деструктор
	~Potion();

#pragma region Сеттеры

	// Сеттер для id эффекта
	void setEffectId(int id);

	// Сеттер для цены
	void setPrice(int price);

	// Сеттер для кол-ва зелья у пользователя
	void setNumber(int number);

	// Сеттер для мощности
	void setPower(int power);

#pragma endregion Сеттеры

#pragma region Геттеры

	// Геттер для кол-ва зелья у пользователя
	int getNumber();

	// Геттер для id эффекта 
	int getEffectId();

	// Геттер для мощности
	int getPower();

	// Геттер для цены
	int getPrice();

#pragma endregion Геттеры

	// Увеличить кол-во зелья
	void increaseNumber();

	// уменьшить кол-во зелья на определенное число
	void decreaseNumber(int number);

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