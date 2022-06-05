#pragma once

#include "Effect.h"
//#include <vector>
#include <map>

#define NUMBER_OF_EFFECTS			2		// Кол-во эффектов

#define MIN_PRICE					4		// Минимальная цена ингредиента
#define MAX_PRICE					135		// Максимальная цена ингредиента

#define UNKNOWN						false	// Неизвестный пользователю эффект	

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

	// Узнать известен ли пользователю эффект у данного ингредиента по id
	bool getEffectIsKnown(int number);

	// Получить итератор на начало ассоциативного массива
	map<int, bool>::iterator getIteratorOfEffectsId();
	
	// Получить имя
	string getName();

	// Получить кол-во
	int getNumber();

	// Геттер для цены
	int getPrice();

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

	//// Массив эффекторов из 2х ингредиентов
	//vector<int> effectsId;

	// Массив эффектов из 2х ингредиентов и их значений известности игроку
	map<int, bool> effectsId;

	//// Метод очистки памяти
	//void clear();
};

