#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyProgramParser.h"

// Строитель таблицы ингредиентов
class IngredientsTableBuilder
{
public:

	// Конструктор по умолчанию
	IngredientsTableBuilder();

	~IngredientsTableBuilder();

	IngredientsTable* getResult();

	// Сеттер строителя ингредиентов
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

	// Построить ингредиент
	void buildIngredientsTable(AlchemyProgramParser* alchemyProgramParser);

private:
	
	// Таблица ингредиентов
	IngredientsTable* ingredientsTable;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	// Сборосить до начальных установок
	void reset();

	// Чистит память
	void clear();

	// Добавить ингредиенты в таблицу
	void addIngredients(int numberOfIngredients);
};

