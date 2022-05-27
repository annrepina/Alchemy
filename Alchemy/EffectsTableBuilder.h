#pragma once
#include "EffectsTable.h"
#include "AlchemyProgramParser.h"
#include "EffectBuilder.h"

// Строитель таблицы эффектов
class EffectsTableBuilder
{
public:

	// Конструктор по умолчанию
	EffectsTableBuilder();

	// Деструктор
	~EffectsTableBuilder();

	// Строит таблицу эффектов
	void buildEffectstable(AlchemyProgramParser* alchemyProgramParser);

	// Добавить эффекты
	void addEffects(int numberOfEffects, bool isPositive);

	//// Добавить позитивные эффекты
	//void addPositiveEffects(int numberOfEffects);

	//// Добавить негативные эффекты
	//void addNegativeEffects(int numberOfEffects);

	// Получить результат
	EffectsTable* getResult();

private:

	EffectsTable* effectsTable;

	EffectBuilder* effectBuilder;

	// Сбрасывает до начальных установок
	void reset();

	// Очищает память
	void clear();


};

