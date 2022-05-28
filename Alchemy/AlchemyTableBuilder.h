#pragma once
#include "AlchemyProgramParser.h"
#include "Builder.h"

// ��������� �������
class AlchemyTableBuilder : public Builder
{
public:

	// ����������� �� ���������
	AlchemyTableBuilder();

	//// ����������
	//virtual ~AlchemyTableBuilder() = 0;

	// ��������� �������
	virtual void buildTable(AlchemyProgramParser* alchemyProgramParser) = 0;

protected:

	//// ��������� �� ��������� ���������
	//virtual void reset() = 0;

	//// ������ ������
	//virtual void clear() = 0;

private:



};

