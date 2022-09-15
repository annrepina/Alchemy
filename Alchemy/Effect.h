#pragma once
#include <string>

using namespace std;

// Эффект ингредиента
class Effect
{
public:

#pragma region Конструкторы

	// Конструктор по умолчанию
	Effect();

	// Конструктор с параметрами
	Effect(string name, bool isPositive);

	// Деструктор
	~Effect();

#pragma endregion Конструкторы

#pragma region Сеттеры

	// Сеттер имени
	void setName(string name);

	// Сеттер для характеристики эффекта
	void setIsPositive(bool isPositive);

#pragma endregion Сеттеры

	// Получить имя
	string getName();

	// Получить характеристику эффекта
	bool getIsPositive();

	// Печать эффекта
	void print();

private:

	// Название эффекта
	string name;

	// Характеристика эффекта, говорящая позитивный или негативный эффект
	bool isPositive;
};