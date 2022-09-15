#pragma once
#include "AlchemyLogic.h"
#include "AlchemyLogicWriter.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"
#include "Builder.h"

// Строитель класса AlchemyLogic
class AlchemyLogicBuilder : public Builder<AlchemyLogic>
{
public:

	// Строитель по умолчанию
	AlchemyLogicBuilder();

	// Деструктор 
	~AlchemyLogicBuilder() override;

	// Построить программу алхимии
	void buildAlchemyProgram();

	// Задает таблицу эффектов
	void setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter);

private:

	// Строитель таблицы эффектов
	EffectsTableBuilder* effectsTableBuilder;

	// Строитель таблицы ингредиентов
	IngredientsTableBuilder* ingredientsTableBuilder;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	// Чистить память
	void clear() override;
};