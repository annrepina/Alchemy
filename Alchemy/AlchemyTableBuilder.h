#pragma once
#include "AlchemyLogicWriter.h"
#include "Builder.h"

// ��������� ������� � ��������� ������������
template <typename Tab>
class AlchemyTableBuilder : public Builder<Tab>
{
public:

	// ����������� �� ���������
	AlchemyTableBuilder() : Builder<Tab>()
	{

	}

	// ��������� �������
	virtual void buildTable() = 0;

};