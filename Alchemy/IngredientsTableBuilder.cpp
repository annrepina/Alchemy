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

//IngredientsTable* IngredientsTableBuilder::getResult()
//{
//	return this->ingredientsTable;
//}

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

//void IngredientsTableBuilder::reset()
//{
//	this->ingredientsTable = new IngredientsTable();
//}

void IngredientsTableBuilder::clear()
{
	//if (nullptr != this->ingredientsTable)
	//{
	//	delete this->ingredientsTable;
	//	this->ingredientsTable = nullptr;
	//}

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

		// Добавляем ингредиент в таблицу
		this->element->addIngredient(this->ingredientBuilder->getResult());

		// Уменьшаем последний индекс
		--lastIngredientNameIndex;
	}
}

//void IngredientsTableBuilder::calculateLength()
//{
//
//	int length;
//
//	// Длина наибольшего id
//	length = calculateMaxIdStrSize();
//
//	// Длина наибольшего имени ингредиента
//	length += calculateMaxNameSize();
//
//	// Длина наибольшей цены
//	length += to_string(MAX_PRICE).size();
//
//	// Длина наибольшего кол-ва
//	length += calculateMaxNumberStrSize();
//
//	//length +=
//
//}
