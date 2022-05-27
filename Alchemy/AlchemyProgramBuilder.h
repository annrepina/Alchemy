#pragma once
#include "AlchemyProgram.h"
#include "AlchemyProgramParser.h"
#include "EffectsTableBuilder.h"


class AlchemyProgramBuilder
{
public:

	// ��������� �� ���������
	AlchemyProgramBuilder();

	// ���������� 
	~AlchemyProgramBuilder();

	// �������� ��������
	AlchemyProgram* getResult();


	void buildAlchemyProgram();

	// ������ ������� ��������
	void setEffectsTable(AlchemyProgramParser* alchemyProgramParse);

private:

	// ��������� ��������� �������
	AlchemyProgram* alchemyProgram;

	// ��������� ������� ��������
	EffectsTableBuilder* effectsTableBuilder;

	//IngredientsTableBuilder* 

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();
};

