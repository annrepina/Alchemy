#pragma once
#include "EffectsTable.h"
#include "AlchemyLogicWriter.h"
#include "EffectBuilder.h"
#include "AlchemyTableBuilder.h"

// Строитель таблицы эффектов
class EffectsTableBuilder : public AlchemyTableBuilder<EffectsTable>
{
public:

	// Конструктор по умолчанию
	EffectsTableBuilder();

	//// Деструктор
	~EffectsTableBuilder() override;

	// Строит таблицу эффектов
	void buildTable(AlchemyLogicWriter* alchemyLogicWriter) override;

	//// Добавить позитивные эффекты
	//void addPositiveEffects(int numberOfEffects);

	//// Добавить негативные эффекты
	//void addNegativeEffects(int numberOfEffects);

	//// Получить результат
	//EffectsTable* getResult();

private:

	//EffectsTable* effectsTable;

	EffectBuilder* effectBuilder;

	// Добавить эффекты
	void addEffects(int numberOfEffects, bool isPositive);

	//// Сбрасывает до начальных установок
	//void reset() override;

	// Очищает память
	void clear() override;

};

