#pragma once

#include "Effect.h"
#include <vector>

#define MAX_NUMBER_OF_EFFECTS 2

// Класс ингредиент
class Ingredient
{
public:

#pragma region Конструкторы

	// Конструктор по умолчанию
	Ingredient();

	// Деструктор
	~Ingredient();

	//// Конструктор с параметрами
	//Ingredient(string name, float price, vector<Effect*> effects);

#pragma endregion Конструкторы

#pragma region Сеттеры

	// Сеттер для имени
	void setName(string name);

	// Сеттер для цены
	void setPrice(float price);

	//// Сеттер для id
	//void setId(int id);

#pragma endregion Сеттеры

	// Добавить эффект
	void addEffect(int effectId);

private:

	// Счетчик ингредиентов
	static int counter;

	// id Ингредиента
	int id;
	
	// Название ингредиента
	string name;

	// Цена за ингредиент
	float price;

	// Массив эффектов из 2х ингредиентов
	vector<int> effectsId;

	//// Метод очистки памяти
	//void clear();
};

