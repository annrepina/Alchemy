#pragma once
#include "AlchemyLogic.h"
#include "AlchemyLogicWriter.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"
#include "Builder.h"

class AlchemyLogicBuilder : public Builder<AlchemyLogic>
{
public:

	// ��������� �� ���������
	AlchemyLogicBuilder();

	// ���������� 
	~AlchemyLogicBuilder() override;

	//// �������� ��������
	//AlchemyProgram* getResult();

	// ��������� ��������� �������
	void buildAlchemyProgram(AlchemyLogicWriter* alchemyLogicWriter);

	// ������ ������� ��������
	void setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter);

private:

	//// ��������� ��������� �������
	//AlchemyProgram* alchemyProgram;

	// ��������� ������� ��������
	EffectsTableBuilder* effectsTableBuilder;

	// ��������� ������� ������������
	IngredientsTableBuilder* ingredientsTableBuilder;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	//// �������� �� ��������� ���������
	//void reset();

	// ������� ������
	void clear() override;
};

