#pragma once
#include <string>
#include <iostream>

using namespace std;

// Стартовые показатели алхимика
#define START_LEVEL			0
#define START_UP_CAPITAL	100

// Макисмальные показатели алхимика
#define MAX_LEVEL			100

// Класс Алхимик
class Alchemist
{
public:

	// Конструктор по умолчанию
	Alchemist();

#pragma region Сеттеры

	// Сеттер для имени
	void setName(string name);

	// Сеттер для уровня алхимика
	void setAlchemistLevel(int alchemistLevel);

	// Сеттер для уровня продавца
	void setSalesmanLevel(int salesmanLevel);

#pragma endregion Сеттеры

#pragma region Геттеры

	// Геттер для имени
	string getName();

#pragma endregion Геттеры 

	// Увеличить уровень алхимика на 1 
	void increaseAlchemistLevel();

	// Увеличить уровень продажника на 1 
	void increaseSalesmanLevel();

	// Увеличить капитал пользователя на указанную сумму
	void increaseCapital(int value);

	// Печать данных алхимика
	void print();

private:

	// Имя алхимика
	string name;

	// Уровень алхимика
	int alchemistLevel;

	// Уровень продавца
	int salesmanLevel;

	// Капитал пользователя
	int сapital;
};

