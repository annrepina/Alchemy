#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyProgramParser.h"
#include "AlchemyTableBuilder.h"

// ��������� ������� ������������
class IngredientsTableBuilder : public AlchemyTableBuilder
{
public:

	// ����������� �� ���������
	IngredientsTableBuilder();

	~IngredientsTableBuilder() override;

	IngredientsTable* getResult();

	// ������ ��������� ������������
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

	// ��������� ����������
	void buildTable(AlchemyProgramParser* alchemyProgramParser) override;

private:
	
	// ������� ������������
	IngredientsTable* ingredientsTable;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// ��������� �� ��������� ���������
	void reset() override;

	// ������ ������
	void clear() override;

	// �������� ����������� � �������
	void addIngredients(int numberOfIngredients);

	//// ��������� ����� �������
	//void calculateLength() override;
};

