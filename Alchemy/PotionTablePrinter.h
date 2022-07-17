#pragma once
#include "TablePrinter.h"
#include "PotionTable.h"

#define PRICE_LENGTH				4		// ����� ����� "����"
#define NUMBER_LENGTH				6		// ����� ����� "���-��"
#define POWER_LENGTH				8		// ����� ����� "��������"

#define NUMBER_OF_COLUMNS			5		// 4 �������

class PotionTablePrinter : public TablePrinter<PotionTable>
{
public:

	PotionTablePrinter();

	~PotionTablePrinter() override;

	void print(int page) override;

	// ��������� ������ � ���������� �������
	void fillInTableContent() override;

	void printAvailableElements(int page) override;


private:

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

	// ������ ����������� �������
	void printContent(int page) override;

	// ������ ���������� ����������� �������
	void printAvailableContent(int page) override;

#pragma endregion ������ ������



};

