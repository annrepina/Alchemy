#pragma once
//#include "Table.h"

// �����-������ ���������� ���-����
template <typename PrintableObj>
class TablePrinter
{
public:

	TablePrinter()
	{

	}

	virtual ~TablePrinter()
	{

	}

	virtual void print(PrintableObj* printableObj)
	{

	}

protected:

	virtual void calculateLength(PrintableObj* printableObj) = 0;

	int xCoordForTablePrinting;

	int tableLength;

	virtual void calculateXCoordForPrinting(PrintableObj* printableObj)
	{
		this->xCoordForTablePrinting = calculateXCoordInMiddle(this->tableLength);
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




