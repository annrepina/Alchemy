#pragma once
#include "Formatting.h"

#define Y_COORD_FOR_PRINTING		10		// ���������� Y ��� ������

// �����-������ ���������� ���-����
template <typename PrintableTable>
class TablePrinter
{
public:

	TablePrinter()
	{
		this->numberOfColumns = 0;
		this->numberOfLines = 0;
		this->tableLength = 0;
		this->xCoordForPrinting = 0;
		this->yCoordForPrinting = Y_COORD_FOR_PRINTING;
	}

	virtual ~TablePrinter()
	{

	}

	virtual void print(PrintableTable* table) = 0;

protected:

	// ���������� Y ��� ������
	int yCoordForPrinting;

	// ���������� X ��� ������
	int xCoordForPrinting;

	// ����� �������
	int tableLength;

	// ���-�� ��������
	int numberOfColumns;

	// ���-�� �����
	int numberOfLines;

	// ������ � ������� ������� �������
	vector<int> columnWidth;

#pragma region ������ �������

	virtual void calculateLength(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	// ����������� ������ ������� ������� � ���������� ������
	virtual vector<int> calculateColumnWidth(PrintableTable* table) = 0;

	virtual void calculateXCoordForPrinting()
	{
		this->xCoordForPrinting = calculateXCoordInMiddle(this->tableLength);
	}

#pragma endregion ������ �������





	// ������ ����� �������
	virtual void printTableHeader(PrintableTable* table) = 0;


private:

};




