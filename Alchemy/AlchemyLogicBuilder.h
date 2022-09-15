#pragma once
#include "AlchemyLogic.h"
#include "AlchemyLogicWriter.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"
#include "Builder.h"

// ��������� ������ AlchemyLogic
class AlchemyLogicBuilder : public Builder<AlchemyLogic>
{
public:

	// ��������� �� ���������
	AlchemyLogicBuilder();

	// ���������� 
	~AlchemyLogicBuilder() override;

	// ��������� ��������� �������
	void buildAlchemyProgram();

	// ������ ������� ��������
	void setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter);

private:

	// ��������� ������� ��������
	EffectsTableBuilder* effectsTableBuilder;

	// ��������� ������� ������������
	IngredientsTableBuilder* ingredientsTableBuilder;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// ������� ������
	void clear() override;
};