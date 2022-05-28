#include "Table.h"

Table::Table()
{
	this->title = "";
	this->length = 0;
	this->numberOfColumns = 0;
	//this->numberOfLines = 0;
	this->yCoordForPrinting = Y_COORD_FOR_PRINTING;
}

Table::~Table()
{
}

void Table::calculateXCoordForPrinting()
{
	this->xCoordForPrinting = calculateXCoordInMiddle(this->length);
}


