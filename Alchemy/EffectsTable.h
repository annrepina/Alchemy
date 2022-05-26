#pragma once
#include "Effect.h"
#include <vector>

// Таблица эффектов ингредиентов
class EffectsTable
{
public:

	EffectsTable();

	// Добавить эффект
	void addEffect(Effect* effect);

private:

	// Список эффектов
	vector<Effect*> effects;
};

