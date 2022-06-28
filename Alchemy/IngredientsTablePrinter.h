#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"
#include "IObserver.h"

#define MULTIPLIER				3		// ��������� ��� ������� ����� �������

//#define NUMBER_OF_COLUMNS		6		// ���-�� �������
#define OUTER_BORDERS			2		// ������� ������� ������� (����� � ������)
#define GAPS					2		// ���-�� �������� � ������� (1 ����� � 1 ������)


#define PRICE_LENGTH				4		// ����� ����� "����"
#define NUMBER_LENGTH				6		// ����� ����� "���-��"

#define UNKNOWN_EFFECT				"����������"	// ���� ������ � ������� ����������� �����������

// ����������� �������� id name price effect1 effect2 number

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>, IObserver
{
public:

	IngredientsTablePrinter();

	//void print(IngredientsTable* ingredientsTable) override;

	void print(IngredientsTable* table, int page) override;

	

protected:

private:

	void update(int id) override;

#pragma region ������ �������
	
	// ���������� ���-�� ����� � �������
	int calculateNumberOfLines(IngredientsTable* table) override;

	// ���������� ������ �������
	int calculateWidth(IngredientsTable* table) override;

	// ��������� ������������ id
	int calculateMaxId(IngredientsTable* table) override;

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

#pragma endregion ������ �������

#pragma region ������ ������

	// ������ ����� �������
	void printHeader() override;

	// ������ ����������� �������
	void printContent(IngredientsTable* table, int page) override;

#pragma endregion ������ ������

	// ��������� ������ � ���������� �������
	void fillInTableContent(IngredientsTable* table) override;

	// ��������� ���� ������� ������� ���������� �������
	void fillInTableContentForOneElement(int id, IngredientsTable* table);

	//// ������ ����� �������
	//void printHeader(IngredientsTable* table) override;

	// ������ ���������� ����� �������
	//void printInnerFrame(IngredientsTable* table) override;
};

