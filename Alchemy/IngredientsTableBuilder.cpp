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
	// ������

	// ���� ��� ������

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
	// ��������� ������ � ������ ������������
	int lastIngredientNameIndex = numberOfIngredients - 1;

	// ��������� ������ � ������ ��������
	int lastEffectsIndex = this->ingredientBuilder->getEffectsTableSize() - 1;

	//this->ingredientBuilder.

	// � ����� ��������� ������� � �������
	for (int i = 0; i < numberOfIngredients; ++i)
	{
		// ������� ���������� 
		this->ingredientBuilder->buildIngredient(lastIngredientNameIndex, lastEffectsIndex);

		Ingredient* res = this->ingredientBuilder->getResult();

		// ��������� ���������� � �������
		this->element->add(res);

		res->subscribe(this->element);

		// ��������� ��������� ������
		--lastIngredientNameIndex;
	}
}
