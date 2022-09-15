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

	// Деструктор
	~EffectsTableBuilder() override;

	// Строит таблицу эффектов
	void buildTable() override;

private:

	// СТроитель эффектов
	EffectBuilder* effectBuilder;

	// Добавить эффекты
	void addEffects(int numberOfEffects, bool isPositive);

	// Очищает память
	void clear() override;

};