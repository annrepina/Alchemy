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
class IngredientsTable : public Table<Ingredient>, public IObservable, public IObserver
{
public:

	// Конструктор по умолчанию
	IngredientsTable();

	~IngredientsTable() override;

	// Добавить ингредиент в таблицу
	void add(Ingredient* ingredient) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	void update(int id, bool isNewElement) override;

	void update(int id, int previousNumber) override;

	void update() override;

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

	//void subscribe(IObserver* observer) override;

	//void unsubscribe(IObserver* observer) override;

	//void notify(int id) override;

	// уменьшить кол-во ингредиента
	void decreaseNumberOfIngredient(int ingredientId, int number);

private:

	// Id ингредиента
	static int id;

	// Ингредиенты
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();
};

