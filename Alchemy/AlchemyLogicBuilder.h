#pragma once
#include "AlchemyLogic.h"
#include "AlchemyProgramParser.h"
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
	void buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse);

	// ������ ������� ��������
	void setEffectsTable(AlchemyProgramParser* alchemyProgramParse);

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

