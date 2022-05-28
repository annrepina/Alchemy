#pragma once
#include "AlchemyProgramParser.h"

// ��������� �������
class AlchemyTableBuilder
{
public:

	// ����������� �� ���������
	AlchemyTableBuilder();

	// ����������
	virtual ~AlchemyTableBuilder() = 0;

	// ��������� �������
	virtual void buildTable(AlchemyProgramParser* alchemyProgramParser) = 0;

protected:

	// ��������� �� ��������� ���������
	virtual void reset() = 0;

	// ������ ������
	virtual void clear() = 0;

	//// ��������� ����� �������
	//virtual void calculateLength() = 0;

private:



};

