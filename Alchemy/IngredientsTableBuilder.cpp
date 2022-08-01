#include "IngredientsTableBuilder.h"

IngredientsTableBuilder::IngredientsTableBuilder() : AlchemyTableBuilder()
{
	//reset();
	this->ingredientBuilder = nullptr;
}

IngredientsTableBuilder::~IngredientsTableBuilder()
{
	clear();
}

void IngredientsTableBuilder::setIngredientBuilder(IngredientBuilder* ingredientBuilder)
{
	this->ingredientBuilder = ingredientBuilder;
}

void IngredientsTableBuilder::buildTable(AlchemyProgramParser* alchemyProgramParser)
{
	// Парсим

	// ЕСЛИ док пустой

	//this->ingredientBuilder = new IngredientBuilder();

	//this->ingredientBuilder->setEffectsTable(effectsTable);

	this->addIngredients(NUMBER_OF_INGREDIENTS);

	this->element->setEffectsTable(this->ingredientBuilder->getEffectsTable());
}

void IngredientsTableBuilder::clear()
{
	AlchemyTableBuilder::clear();

	if (nullptr != this->ingredientBuilder)
	{
		delete this->ingredientBuilder;
		this->ingredientBuilder = nullptr;
	}
}

void IngredientsTableBuilder::addIngredients(int numberOfIngredients)
{
	// Последний индекс в списке ингредиентов
	int lastIngredientNameIndex = numberOfIngredients - 1;

	// Последний индекс в списке эффектов
	int lastEffectsIndex = this->ingredientBuilder->getEffectsTableSize() - 1;

	//this->ingredientBuilder.

	// В цикле добавляем эффекты в таблицу
	for (int i = 0; i < numberOfIngredients; ++i)
	{
		// Создаем ингредиент 
		this->ingredientBuilder->buildIngredient(lastIngredientNameIndex, lastEffectsIndex);

		Ingredient* res = this->ingredientBuilder->getResult();

		// Добавляем ингредиент в таблицу
		this->element->add(res);

		res->subscribe(this->element);

		// Уменьшаем последний индекс
		--lastIngredientNameIndex;
	}
}
