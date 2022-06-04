#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"

#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

#define NUMBER_OF_COLUMNS		6		// ���-�� �������
#define OUTER_BORDERS			2		// ������� ������� ������� (����� � ������)
#define GAPS					2		// ���-�� �������� � ������� (1 ����� � 1 ������)




// ����������� �������� id name price effect1 effect2 number

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	IngredientsTablePrinter();

	//void print(IngredientsTable* ingredientsTable) override;

protected:

private:
	
	// ���������� ������ �������
	int calculateWidth(IngredientsTable* ingredientsTable) override;

	// ������� ���������� id
	int calculateMaxIdStrSize(IngredientsTable* table) override;

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize(IngredientsTable* table) override;

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize(IngredientsTable* table);

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize(IngredientsTable* table);

	// ����������� ������ ������� ������� � ���������� ������
	vector<int> calculateColumnWidth(IngredientsTable* table) override;

	//// ������ ����� �������
	//void printHeader(IngredientsTable* table) override;

	

	// ������ ���������� ����� �������
	//void printInnerFrame(IngredientsTable* table) override;
};

