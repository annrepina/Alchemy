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
	// ������

	// ���� ��� ������

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

		// ��������� ���������� � �������
		this->element->addIngredient(this->ingredientBuilder->getResult());

		// ��������� ��������� ������
		--lastIngredientNameIndex;
	}
}

//void IngredientsTableBuilder::calculateLength()
//{
//
//	int length;
//
//	// ����� ����������� id
//	length = calculateMaxIdStrSize();
//
//	// ����� ����������� ����� �����������
//	length += calculateMaxNameSize();
//
//	// ����� ���������� ����
//	length += to_string(MAX_PRICE).size();
//
//	// ����� ����������� ���-��
//	length += calculateMaxNumberStrSize();
//
//	//length +=
//
//}
