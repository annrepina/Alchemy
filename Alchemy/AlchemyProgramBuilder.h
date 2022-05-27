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

private:

	// ��������� ��������� �������
	AlchemyProgram* alchemyProgram;

	// �������� �� ��������� ���������
	void reset();

	// ������� ������
	void clear();
};

