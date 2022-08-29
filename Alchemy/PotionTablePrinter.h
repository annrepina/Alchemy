#pragma once
#include "TablePrinter.h"
#include "PotionTable.h"

#define PRICE_LENGTH				4		// ����� ����� "����"
#define NUMBER_LENGTH				6		// ����� ����� "���-��"
#define POWER_LENGTH				8		// ����� ����� "��������"

#define NUMBER_OF_COLUMNS			5		// 5 �������

class PotionTablePrinter : public TablePrinter<PotionTable>/*, public IObserver*/
{
public:

	PotionTablePrinter();

	~PotionTablePrinter() override;

	void print(int page) override;

	void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) override;

	void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) override;

	// ��������� ������ � ���������� �������
	void fillInTableContent() override;

	void printAvailableElements(int page) override;

	void update() override;

private:

	//void update(int id) override;

#pragma region ������ �������

	// ���������� ���-�� ����� � �������
	int calculateNumberOfLines() override;

	// ����������� ������ ������� ������� � ���������� ������
	vector<int> calculateColumnWidth() override;

	// ���������� ������ �������
	int calculateWidth() override;

	// ��������� ������������ id
	int calculateMaxId() override;

	//// ������� ���������� id
	//int calculateMaxIdStrSize() override;

	// ������� ����� ������� �������� �����������
	int calculateMaxNameSize() override;

	// ������� ���������� ���-�� ������������
	int calculateMaxNumberStrSize() override;

	// ���������� ���� ����� ����������� ����������� �������� �����
	int calculateMaxPowerStrSize();

	// ��������� ���� ����� ����������� ����������� ����
	int calculateMaxPriceStrSize();





#pragma endregion ������ �������

#pragma region ������ ������

	// ������ ����� �������
	void printHeader() override;

	void printHeader(int numberOfColumn, bool ordreOfSorting) override;

	// ������ ����������� �������
	void printContent(int page) override;

	void printContent(vector<vector<string>> content, int page) override;

	// ������ ���������� ����������� �������
	void printAvailableContent(int page) override;

#pragma endregion ������ ������

	// ��������� ���� ������� ������� ���������� �������
	void changeTableContentForOneElement(int id) override;

	// ��������� ���� ������� ������� ���������� �������
	void changeTableContentForOneElement(int id, int previousNumber) override;

	// �������� ���������� ������� - �������� ����� ����������
	void addElementToTableContent(int id) override;

	// ����� ������ �������� �������� � ������� �������� �� �����
	int findIndexInTableContentByKey(int key);
};

