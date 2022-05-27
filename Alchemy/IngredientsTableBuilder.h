#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyProgramParser.h"

// ��������� ������� ������������
class IngredientsTableBuilder
{
public:

	// ����������� �� ���������
	IngredientsTableBuilder();

	~IngredientsTableBuilder();

	IngredientsTable* getResult();

	// ��������� ����������
	void buildIngredientsTable(AlchemyProgramParser* alchemyProgramParser);

private:
	
	// ������� ������������
	IngredientsTable* ingredientsTable;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// ��������� �� ��������� ���������
	void reset();

	// ������ ������
	void clear();
};

