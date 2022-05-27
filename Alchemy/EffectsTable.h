#pragma once
#include "Effect.h"
#include <map>

// Таблица эффектов ингредиентов
class EffectsTable
{
public:

	// 
	EffectsTable();

	~EffectsTable();

	// Добавить эффект
	void addEffect(Effect* effect);

	// Печать таблицы
	void print();

private:

	// Список эффектов
	//vector<Effect*> effects;

	// Id эффекта
	static int id;

	// Список эффектов
	map<int, Effect*> effectsWithId;

	// Очищает память
	void clear();
};

