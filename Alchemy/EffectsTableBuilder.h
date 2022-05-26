#pragma once
#include "EffectsTable.h"
#include "AlchemyProgramParser.h"
#include "EffectBuilder.h"

// Строитель таблицы эффектов
class EffectsTableBuilder
{
public:

	EffectsTableBuilder();

	void setEffectstable(AlchemyProgramParser* alchemyProgramParser);

private:

	EffectsTable* effectstable;

	EffectBuilder* effectBuilder;

	// Добавить позитивные эффекты
	void addPositiveEffects(int numberOfEffects);
};

