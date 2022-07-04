#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>
#include "IObservable.h"

//#define NUMBER_OF_COLUMNS			6		// Кол-во колонок
//#define OUTER_BORDERS				2		// Внешние границы таблицы (левая и правая)

//#define MULTIPLIER				3		// Множитель для расчета длины таблицы

// Таблица ингредиентов
class IngredientsTable : public Table<Ingredient>, public IObservable
{
public:

	// Конструктор по умолчанию
	IngredientsTable();

	~IngredientsTable() override;

	// Добавить ингредиент в таблицу
	void add(Ingredient* ingredient) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

#pragma region ГЕТТЕРЫ

	// Получить итератор на последний элемент в map
	map<int, Ingredient*>::iterator getEndIterator();

	// Получить итератор на первый элемент в map
	map<int, Ingredient*>::iterator getStartIterator();

	//// Получить map
	//map<int, Ingredient*> getIngredientsWithId();

	// Получить таблицу эффектов
	EffectsTable* getEffectsTable();

	// Получить ингредиент по id 
	Ingredient* getIngredientById(int id);

	// Получить ингредиент по id 
	Ingredient* getIngredientByName(string name);

	// получить ключ по значению
	int getIdByIngredient(Ingredient* ingredient);

#pragma endregion ГЕТТЕРЫ

	void subscribe(IObserver* observer) override;

	void unsubscribe(IObserver* observer) override;

	void notify(int id) override;

private:

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();



	//// Вернуть наибольший id
	//int calculateMaxIdStrSize();

	//// Вернуть самое длинное название ингредиента
	//int calculateMaxNameSize();

	//// Вернуть наибольшее кол-во ингредиентов
	//int calculateMaxNumberStrSize();

	//// Посчитать размеры максимальных имен эффектов
	//int calculateMaxEffectNameSize();

	//// Хранит максимальные размеры имен эффектов
	//int effectsNameSizes[NUMBER_OF_EFFECTS];

};

