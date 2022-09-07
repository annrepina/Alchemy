#pragma once
#include "AlchemyLogic.h"
#include "AlchemyLogicWriter.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"
#include "Builder.h"

class AlchemyLogicBuilder : public Builder<AlchemyLogic>
{
public:

	// Строитель по умолчанию
	AlchemyLogicBuilder();

	// Деструктор 
	~AlchemyLogicBuilder() override;

	//// Получить результа
	//AlchemyProgram* getResult();

	// Построить программу алхимии
	void buildAlchemyProgram(AlchemyLogicWriter* alchemyLogicWriter);

	// Задает таблицу эффектов
	void setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter);

private:

	//// Экземпляр программы алхимии
	//AlchemyProgram* alchemyProgram;

	// Строитель таблицы эффектов
	EffectsTableBuilder* effectsTableBuilder;

	// Строитель таблицы ингредиентов
	IngredientsTableBuilder* ingredientsTableBuilder;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	//// Сбросить до начальных установок
	//void reset();

	// Чистить память
	void clear() override;
};

