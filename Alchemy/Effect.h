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

	// Сеттер для булевой
	void setIsPositive(bool isPositive);

#pragma endregion Сеттеры

	// Получить имя
	string getName();

	// Печать эффекта
	void print();

private:

	//// Счетчик эффектов
	//static int counter;

	//// id эффекта
	//int id;

	// Название эффекта
	string name;

	// Булева переменная, отвечающая позитивный или негативный эффект
	bool isPositive;


};

