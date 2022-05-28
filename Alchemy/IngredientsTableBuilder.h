#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyProgramParser.h"
#include "AlchemyTableBuilder.h"

// Строитель таблицы ингредиентов
class IngredientsTableBuilder : public AlchemyTableBuilder
{
public:

	// Конструктор по умолчанию
	IngredientsTableBuilder();

	~IngredientsTableBuilder() override;

	IngredientsTable* getResult();

	// Сеттер строителя ингредиентов
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

	// Построить ингредиент
	void buildTable(AlchemyProgramParser* alchemyProgramParser) override;

private:
	
	// Таблица ингредиентов
	IngredientsTable* ingredientsTable;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	// Сборосить до начальных установок
	void reset() override;

	// Чистит память
	void clear() override;

	// Добавить ингредиенты в таблицу
	void addIngredients(int numberOfIngredients);

	//// Расчитать длину таблицы
	//void calculateLength() override;
};

