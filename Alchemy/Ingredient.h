#pragma once
#include "Effect.h"
#include "IObservable.h"
#include <map>

#define NUMBER_OF_EFFECTS			2		// Кол-во эффектов

#define MIN_PRICE					4		// Минимальная цена ингредиента
#define MAX_PRICE					135		// Максимальная цена ингредиента

#define UNKNOWN						false	// Неизвестный пользователю эффект	
#define KNOWN						true	// Известный пользователю эффект

// Класс ингредиент
class Ingredient : public IObservable
{
public:

	// Конструктор по умолчанию
	Ingredient();

	// Деструктор
	~Ingredient();

	// Печать
	void print();

#pragma region ГЕТТЕРЫ

	// Узнать известен ли пользователю эффект у данного ингредиента по номеру эффекта
	bool getEffectIsKnown(int number);

	// Получить итератор на начало ассоциативного массива effectsId
	map<int, bool>::iterator getBeginIteratorOfEffectsId();

	// Получить итератор на конец ассоциативного массива effectsId
	map<int, bool>::iterator getEndIteratorOfEffectsId();
	
	// Получить имя
	string getName();

	// Получить кол-во
	int getNumber();

	// Геттер для цены
	int getPrice();

	// Геттер для кол-ва эффектов
	int getNumberOfEffects();

#pragma endregion ГЕТТЕРЫ

#pragma region Сеттеры

	// Сеттер для имени
	void setName(string name);

	// Сеттер для цены
	void setPrice(float price);

	// Сеттер для кол-ва
	void setNumber(int number);

	// Открыть эффект по id
	void openEffect(int id);

	// Открыть эффект рандомно
	void openEffectRandomly();

#pragma endregion Сеттеры

	// Добавить эффект
	void addEffect(int effectId);

	// Добавить эффект с характеристикой
	void addEffectWithCharacteristic(int effectId, bool characteristic);

	// Увеличить кол-во ингредиента на опред число
	void increaseNumber(int number);

	// уменьшить кол-во ингредиентов на опред число
	void decreaseNumber(int number);

private:

	// Кол-во эффектов
	const static int numberOfEffects = NUMBER_OF_EFFECTS;
	
	// Название ингредиента
	string name;

	// Цена за ингредиент
	int price;

	// Кол-во ингредиента у алхимика
	int number;

	// Массив эффектов из 2х ингредиентов и их значений известности игроку
	map<int, bool> effectsId;
};

