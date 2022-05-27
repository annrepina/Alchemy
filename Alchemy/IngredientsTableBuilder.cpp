#include "IngredientsTableBuilder.h"

IngredientsTableBuilder::IngredientsTableBuilder()
{
	reset();
	this->ingredientBuilder = nullptr;
}

IngredientsTableBuilder::~IngredientsTableBuilder()
{
	clear();
}

IngredientsTable* IngredientsTableBuilder::getResult()
{
	return this->ingredientsTable;
}

void IngredientsTableBuilder::buildIngredientsTable(AlchemyProgramParser* alchemyProgramParser)
{
	// Парсим

	// ЕСЛИ док пустой

	this->ingredientBuilder = new IngredientBuilder();

	//this-
}

void IngredientsTableBuilder::reset()
{
	this->ingredientsTable = new IngredientsTable();
}

void IngredientsTableBuilder::clear()
{
	if (nullptr != this->ingredientsTable)
	{
		delete this->ingredientsTable;
		this->ingredientsTable = nullptr;
	}

	if (nullptr != this->ingredientBuilder)
	{
		delete this->ingredientBuilder;
		this->ingredientBuilder = nullptr;
	}
}
