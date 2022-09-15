#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyLogicWriter.h"
#include "AlchemyTableBuilder.h"

// ��������� ������� ������������
class IngredientsTableBuilder : public AlchemyTableBuilder<IngredientsTable>
{
public:

	// ����������� �� ���������
	IngredientsTableBuilder();

	// ����������
	~IngredientsTableBuilder() override;

	// ������ ��������� ������������
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

	// ��������� ����������
	void buildTable() override;

private:

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// ������ ������
	void clear() override;

	// �������� ����������� � �������
	void addIngredients(int numberOfIngredients);
};
