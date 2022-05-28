#pragma once
#include "AlchemyProgram.h"
#include "AlchemyProgramParser.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"
#include "Builder.h"

class AlchemyProgramBuilder : public Builder<AlchemyProgram>
{
public:

	// Строитель по умолчанию
	AlchemyProgramBuilder();

	// Деструктор 
	~AlchemyProgramBuilder() override;

	//// Получить результа
	//AlchemyProgram* getResult();

	// Построить программу алхимии
	void buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse);

	// Задает таблицу эффектов
	void setEffectsTable(AlchemyProgramParser* alchemyProgramParse);

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

