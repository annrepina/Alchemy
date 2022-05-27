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

	// ������ ��������� ������������
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

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

	// �������� ����������� � �������
	void addIngredients(int numberOfIngredients);
};

