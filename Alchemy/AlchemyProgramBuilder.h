#pragma once
#include "AlchemyProgram.h"
#include "AlchemyProgramParser.h"
#include "EffectsTableBuilder.h"
#include "IngredientsTableBuilder.h"

class AlchemyProgramBuilder
{
public:

	// ��������� �� ���������
	AlchemyProgramBuilder();

	// ���������� 
	~AlchemyProgramBuilder();

	// �������� ��������
	AlchemyProgram* getResult();

	// ��������� ��������� �������
	void buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse);

	// ������ ������� ��������
	void setEffectsTable(AlchemyProgramParser* alchemyProgramParse);

private:

	// ��������� ��������� �������
	AlchemyProgram* alchemyProgram;

	// ��������� ������� ��������
	EffectsTableBuilder* effectsTableBuilder;

	// ��������� ������� ������������
	IngredientsTableBuilder* ingredientsTableBuilder;

	// ��������� ������������
	IngredientBuilder* ingredientBuilder;

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();
};

