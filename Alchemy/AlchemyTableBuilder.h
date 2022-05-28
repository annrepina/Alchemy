#pragma once
#include "AlchemyProgramParser.h"
#include "Builder.h"

// ��������� �������
template <typename Tab>
class AlchemyTableBuilder : public Builder<Tab>
{
public:

	// ����������� �� ���������
	AlchemyTableBuilder() : Builder<Tab>()
	{

	}

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

