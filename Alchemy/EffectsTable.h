#pragma once
#include "Effect.h"
#include "Table.h"
#include <map>

// Таблица эффектов ингредиентов
class EffectsTable : public Table<Effect>
{
public:

	// Конструктор по умолчанию
	EffectsTable();

	// Деструктор
	~EffectsTable() override;

	// Добавить эффект
	void add(Effect* effect) override;

	// Добавить эффект
	void add(Effect* effect, int id) override;

	// Печать таблицы
	void print();

#pragma region Геттеры

	// геттер для статик id 
	int getId();

	// Геттер для размера
	int getSize();

	// Получить эффект по ключу
	Effect* getEffectByKey(int key);

	// Получить итератор на начало map
	map<int, Effect*>::iterator getStartIterator();
	
	// Получить итератор на начало map
	map<int, Effect*>::iterator getEndIterator();

#pragma endregion Геттеры

#pragma region Сеттеры

	// Сеттер для статик id
	void setId(int id);

#pragma endregion Сеттеры

private:

	// Id эффекта
	static int id;

	// Размер таблицы
	int size;

	// Список эффектов
	map<int, Effect*> effectsWithId;

	// Очищает память
	void clear();
};