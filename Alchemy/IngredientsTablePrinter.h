#pragma once
#include "TablePrinter.h"
#include "IngredientsTable.h"
#include "IObserver.h"
#include "ServiceFunctions.h"

#define MULTIPLIER									3		// ��������� ��� ������� ����� �������

#define OUTER_BORDERS								2		// ������� ������� ������� (����� � ������)
#define GAPS										2		// ���-�� �������� � ������� (1 ����� � 1 ������)
#define NUMBER_OF_COLUMNS							6		// ���-�� �������
#define NUMBER_OF_COLUMN_WITH_NUMBER_OF_INGREDIENTS	6		// ����� �������, � ������� ��������� ���-�� ������������

#define PRICE_LENGTH								4		// ����� ����� "����"
#define NUMBER_LENGTH								6		// ����� ����� "���-��"

#define UNKNOWN_EFFECT								"����������"	// ���� ������ � ������� ����������� �����������

// �������� ������� � �������
#define INGREDIENT_TABLE_DIGIT_COLUMN_1			1	// ������� 1
#define INGREDIENT_TABLE_DIGIT_COLUMN_3			3	// ������� 3
#define INGREDIENT_TABLE_DIGIT_COLUMN_6			6	// ������� 6

#define INDEX_IF_CONTENT_OF_NUMBER_COLUMN		5	// ������ �������� ������� � ���-���

// �����, ���������� ������� ������������ - ������� ������� ������������
class IngredientsTablePrinter : public TablePrinter<IngredientsTable>
{
public:

	// ����������� �� ���������
	IngredientsTablePrinter();

	// ����������
	~IngredientsTablePrinter() override;

	// ������ �������
	void print(int page) override;

	// ������ ������������� �������� �������� �������� �������
	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	// ������ � ��������� �����������
	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	// ������ ��������� ���������, ���-�� � ������� ������ ����
	void printAvailableElements(int page) override;

	// ��������� ������ � ���������� �������
	void fillInTableContent() override;

	// ��������� ������ ��� ������
	void calculateData() override;

	// ������ ���-�� ��������� ���������
	int getNumberOfAvailableContent();

private:

	// ���-�� ��������� ������������ ���������
	int numberOfAvailableContent;

#pragma region ������ �������
	
	// ���������� ���-�� ����� � �������
	int calculateNumberOfLines() override;

	// ���������� ������ �������
	int calculateWidth() override;

	// ��������� ������ ����� - ������������� id
	int calculateMaxId() override;

	// ��������� ������ ������ �������� �������� �����������
	int calculateMaxNameSize() override;

	// ��������� ������ ����� - ���������� ���-�� ������������
	int calculateMaxNumberStrSize() override;

	// ��������� ������� ������������ ���� ��������
	int calculateMaxEffectNameSize();

	// ����������� ������ ������� ������� � ���������� ������
	vector<int> calculateColumnWidth() override;

	// ��������� ���-�� ��������� ������������ ������������
	int calculateNumberOfAvailableElements();

#pragma endregion ������ �������

#pragma region ������ ������

	// ������ ����� �������
	void printHeader() override;

	// ������ ����� ������� � ��������� ����������
	void printHeader(int numberOfColumn, bool ordreOfSorting) override;

	// ������ ����������� �������
	void printContent(int page) override;

	// ������ �������� ������������� ��������
	void printContent(vector<vector<string>> content, int page) override;

	// ������ ���������� ����������� �������
	void printAvailableContent(int page) override;

#pragma endregion ������ ������

	// �������m ������� ��� ������ ������������� ����������� �� id 
	void changeTableContentForOneElement(int id) override;

	// �������m ������� ��� ������ ������������� ����������� �� id � ������ ���-��
	void changeTableContentForOneElement(int id, int previousNumber) override;

	// �������� ���������� ������� - �������� ����� ����������
	void addElementToTableContent(int id) override;
};