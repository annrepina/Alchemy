#pragma once
#include "AlchemyProgram.h"


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

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();
};

