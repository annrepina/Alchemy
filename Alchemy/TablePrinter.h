#pragma once
#include "Table.h"

// �����-������ ���������� ���-����
//template <typename PrintableObj>
class TablePrinter
{
public:

	TablePrinter();

	virtual ~TablePrinter();

protected:

	virtual void print(Table* printableObj);

	virtual void calculateLength() = 0;

	int xCoordForTablePrinting;

	int tableLength;

	virtual void calculateXCoordForPrinting(Table* printableObj);

private:







};

