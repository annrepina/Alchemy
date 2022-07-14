#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"

// Класс таблица зелий
class PotionTable : public Table<Potion>
{
public:

	PotionTable();

	~PotionTable() override;

	// Добавить зелье в таблицу
	void add(Potion* potion) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

#pragma region Геттеры

	// Получить итератор на последний элемент в map
	map<int, Potion*>::iterator getEndIterator();

	// Получить итератор на последний элемент в map
	map<int, Potion*>::iterator getStartIterator();

	EffectsTable* getEffectsTable();

#pragma endregion Геттеры

private:

	// Id зелья
	static int id;

	// Ингредиенты
	map<int, Potion*> potiontsWithId;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Чистит память
	void clear();
};

