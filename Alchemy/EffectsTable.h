#pragma once
#include "Effect.h"
#include "Table.h"
#include <map>

// Таблица эффектов ингредиентов
class EffectsTable : public Table
{
public:

	// Конструктор по умолчанию
	EffectsTable();

	~EffectsTable() override;

	// Добавить эффект
	void addEffect(Effect* effect);

	// Печать таблицы
	void print() const override;

	// Геттер для размера
	int getSize();

	// Получить эффект по ключу
	Effect* getEffectByKey(int key);

private:

	// Список эффектов
	//vector<Effect*> effects;

	// Id эффекта
	static int id;

	// Размер таблицы
	int size;

	// Список эффектов
	map<int, Effect*> effectsWithId;

	// Очищает память
	void clear();
};

