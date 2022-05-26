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

	// Добавить эффекты
	void addEffects(int numberOfEffects, bool isPositive);

	//// Добавить позитивные эффекты
	//void addPositiveEffects(int numberOfEffects);

	//// Добавить негативные эффекты
	//void addNegativeEffects(int numberOfEffects);

private:

	EffectsTable* effectstable;

	EffectBuilder* effectBuilder;


};

