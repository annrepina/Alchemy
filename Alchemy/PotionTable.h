#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"
#include "IObservable.h"

// Класс таблица зелий
class PotionTable : public Table<Potion>, public IObservable, public IObserver
{
public:

	// Конструктор по умолчанию
	PotionTable();

	// Деструктор
	~PotionTable() override;

	// Добавить зелье в таблицу
	void add(Potion* potion) override;

	// Добавить зелье в таблицу с id 
	void add(Potion* element, int id) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Сеттер для статик id 
	void setId(int id);

	// Возвращает id Зелья, если такое было, иначе -1
	int hasSuchPotion(Potion* potion);

	// Обновляет таблицу исходя из измениния объекта подписки - Potion
	void update(int id, bool isNewElement) override;

	// Обновляет таблицу исходя из измениния объекта подписки - Potion
	void update(int id, int previousNumber) override;

	// Обновляет таблицу исходя из измениния объекта подписки - Potion
	void update() override;

	// уменьшить кол-во зелья
	void decreaseNumberOfPotion(int potionId, int number);

#pragma region Геттеры

	// Получить итератор на последний элемент в map potiontsWithId
	map<int, Potion*>::iterator getEndIterator();

	// Получить итератор на последний элемент в map potiontsWithId
	map<int, Potion*>::iterator getStartIterator();

	// Получить таблицу эффектов
	EffectsTable* getEffectsTable();

	// Получить зелье по id
	Potion* getPotionById(int id);

	// Получить размер таблицы (кол-во элементов)
	int getSize();

	// Получить статик id 
	int getId();

#pragma endregion Геттеры

private:

	// Id вновь созданного зелья
	static int id;

	// Ингредиенты с id 
	map<int, Potion*> potiontsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();
};