#pragma once

#include "Effect.h"
#include <vector>

#define NUMBER_OF_EFFECTS			2		// Кол-во эффектов

#define MIN_PRICE					4		// Минимальная цена ингредиента
#define MAX_PRICE					135		// Максимальная цена ингредиента

// Класс ингредиент
class Ingredient
{
public:

#pragma region Конструкторы

	// Конструктор по умолчанию
	Ingredient();

	// Деструктор
	~Ingredient();

	// Печать
	void print();

#pragma region ГЕТТЕРЫ

	// Получить id эффекта по номеру
	int getEffectId(int number);
	
	// Получить имя
	string getName();

#pragma endregion ГЕТТЕРЫ

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

	//// Счетчик ингредиентов
	//static int counter;

	//// id Ингредиента
	//int id;
	
	// Название ингредиента
	string name;

	// Цена за ингредиент
	int price;

	// Кол-во
	int number;

	// Массив эффекторов из 2х ингредиентов
	vector<int> effectsId;

	//// Метод очистки памяти
	//void clear();
};

