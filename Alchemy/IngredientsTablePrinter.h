#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

#define NUMBER_OF_COLUMNS		6		// ���-�� �������
#define OUTER_BORDERS			2		// ������� ������� ������� (����� � ������)

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	IngredientsTablePrinter();

	void print(IngredientsTable* ingredientsTable) override;


	

protected:

private:

	void calculateLength(IngredientsTable* ingredientsTable) override;

	// ������� ���������� id
	int calculateMaxIdStrSize(Table* table);

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize();

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize();

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize();


};

