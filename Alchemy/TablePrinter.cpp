#include "TablePrinter.h"

TablePrinter::TablePrinter()
{
	this->xCoordForTablePrinting = 0;
	this->tableLength = 0;
}

TablePrinter::~TablePrinter()
{
}

void TablePrinter::print(Table* printableObj)
{
	printableObj->calculateXCoordForPrinting();

	calculateLength();


}

void TablePrinter::calculateXCoordForPrinting(Table* printableObj)
{
	this->xCoordForTablePrinting = calculateXCoordInMiddle(this->tableLength);
}
