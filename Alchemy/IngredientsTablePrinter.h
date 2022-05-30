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
	int calculateMaxIdStrSize(IngredientsTable* table) override;

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize(IngredientsTable* table) override;

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize(IngredientsTable* table);

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize(IngredientsTable* table);

	// ������ ����� �������
	void printTableHeader(IngredientsTable* table) override;
};

