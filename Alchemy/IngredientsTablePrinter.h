#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

#define NUMBER_OF_COLUMNS		6		// ���-�� �������
#define OUTER_BORDERS			2		// ������� ������� ������� (����� � ������)

class IngredientsTablePrinter : public TablePrinter
{
public:

	IngredientsTablePrinter();


	

protected:

private:

	void calculateLength() override;

	// ������� ���������� id
	int calculateMaxIdStrSize();

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize();

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize();

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize();


};

