#pragma once
#include "Potion.h"
#include "Table.h"
#include "EffectsTable.h"
#include "IObservable.h"

// Класс таблица зелий
class PotionTable : public Table<Potion>, public IObservable, public IObserver
{
public:

	PotionTable();

	~PotionTable() override;

	// Добавить зелье в таблицу
	void add(Potion* potion) override;

	void add(Potion* element, int id) override;

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Возвращает ключ Зелья, если такое было, иначе -1
	int hasSuchPotion(Potion* potion);

	void update(int id, bool isNewElement) override;

	void update(int id, int previousNumber) override;

	void update() override;

	// уменьшить кол-во зелья
	void decreaseNumberOfPotion(int potionId, int number);

#pragma region Геттеры

	// Получить итератор на последний элемент в map
	map<int, Potion*>::iterator getEndIterator();

	// Получить итератор на последний элемент в map
	map<int, Potion*>::iterator getStartIterator();

	EffectsTable* getEffectsTable();

	// Получить зелье по id
	Potion* getPotionById(int id);

	int getSize();

	//// Получить такое же зелье
	//Potion* getSuchPotion(Potion* potion);

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

