#pragma once
#include "Ingredient.h"
#include "EffectsTable.h"
#include "Table.h"
#include <map>
#include "IObservable.h"

// Таблица ингредиентов
class IngredientsTable : public Table<Ingredient>, public IObservable, public IObserver
{
public:

	// Конструктор по умолчанию
	IngredientsTable();

	// Деструктор
	~IngredientsTable() override;

	// Добавить ингредиент в таблицу
	void add(Ingredient* ingredient) override;

	// Добавить ингредиент в таблицу с id
	void add(Ingredient* element, int id) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Сеттре для id 
	void setId(int id);

	// Обновить контент из-за измениния полей объекта подписки - ингредиента
	void update(int id, bool isNewElement) override;

	// Обновить контент из-за измениния полей объекта подписки - ингредиента
	// Указываем число, чтобы если кол-во ингредтиента == 0, удалить id ингредиента из доступных элементов
	void update(int id, int previousNumber) override;

	// Обновить контент из-за измениния полей объекта подписки - ингредиента
	void update() override;

#pragma region ГЕТТЕРЫ

	// Получить итератор на последний элемент в map ingredientsWithId
	map<int, Ingredient*>::iterator getEndIterator();

	// Получить итератор на первый элемент в map ingredientsWithId
	map<int, Ingredient*>::iterator getStartIterator();

	// Получить таблицу эффектов
	EffectsTable* getEffectsTable();

	// Получить ингредиент по id 
	Ingredient* getIngredientById(int id);

	// Получить ингредиент по имени
	Ingredient* getIngredientByName(string name);

	// получить ключ по значению ингредиента
	int getIdByIngredient(Ingredient* ingredient);

	// Получить статик id 
	int getId();

#pragma endregion ГЕТТЕРЫ

	// уменьшить кол-во ингредиента
	void decreaseNumberOfIngredient(int ingredientId, int number);

private:

	// Id вновь созданного ингредиента
	static int id;

	// Ингредиенты с их id 
	map<int, Ingredient*> ingredientsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();
};