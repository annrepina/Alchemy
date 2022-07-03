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

class IngredientsTablePrinter : public TablePrinter<IngredientsTable>, public IObserver
{
public:

	IngredientsTablePrinter();

	~IngredientsTablePrinter() override;

	void print(int page) override;

private:

	void update(int id) override;

#pragma region ������ �������
	
	// ���������� ���-�� ����� � �������
	int calculateNumberOfLines() override;

	// ���������� ������ �������
	int calculateWidth() override;

	// ��������� ������������ id
	int calculateMaxId() override;

	// ������� ���������� id
	int calculateMaxIdStrSize() override;

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize() override;

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize() override;

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize();

	// ����������� ������ ������� ������� � ���������� ������
	vector<int> calculateColumnWidth() override;

#pragma endregion ������ �������

#pragma region ������ ������

	// ������ ����� �������
	void printHeader() override;

	// ������ ����������� �������
	void printContent(int page) override;

#pragma endregion ������ ������

	// ��������� ������ � ���������� �������
	void fillInTableContent() override;

	// ��������� ���� ������� ������� ���������� �������
	void fillInTableContentForOneElement(int id);

	//// ������ ����� �������
	//void printHeader(IngredientsTable* table) override;

	// ������ ���������� ����� �������
	//void printInnerFrame(IngredientsTable* table) override;
};

