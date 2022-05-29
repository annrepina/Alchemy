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

	virtual void calculateLength(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	int xCoordForPrinting;

	int tableLength;

	// ���-�� ��������
	int numberOfColumns;

	// ���-�� �����
	int numberOfLines;

	// ��������� y ��� ������
	int yCoordForPrinting;

	virtual void calculateXCoordForPrinting()
	{
		this->xCoordForPrinting = calculateXCoordInMiddle(this->tableLength);
	}

private:







};




//// �����-������ ���������� ���-����
////template <typename PrintableObj>
//class TablePrinter
//{
//public:
//
//	TablePrinter();
//
//	virtual ~TablePrinter();
//
//	virtual void print(Table* printableObj);
//
//protected:
//
//
//
//	virtual void calculateLength(Table* printableObj) = 0;
//
//	int xCoordForTablePrinting;
//
//	int tableLength;
//
//	virtual void calculateXCoordForPrinting(Table* printableObj);
//
//private:
//
//
//
//
//
//
//
//};




