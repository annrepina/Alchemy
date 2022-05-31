#pragma once
#include "Formatting.h"

#define Y_COORD_FOR_PRINTING		10		// Координата Y для печати

// Класс-шаблон печатающий что-либо
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

	// Координата Y для печати
	int yCoordForPrinting;

	// Координата X для печати
	int xCoordForPrinting;

	// Длина таблицы
	int tableLength;

	// Кол-во столбцов
	int numberOfColumns;

	// Кол-во строк
	int numberOfLines;

	// Вектор с шириной каждого столбца
	vector<int> columnWidth;

#pragma region МЕТОДЫ РАСЧЕТА

	virtual void calculateLength(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	// Расчитывает ширину каждого столбца и возвращает вектор
	virtual vector<int> calculateColumnWidth(PrintableTable* table) = 0;

	virtual void calculateXCoordForPrinting()
	{
		this->xCoordForPrinting = calculateXCoordInMiddle(this->tableLength);
	}

#pragma endregion МЕТОДЫ РАСЧЕТА





	// Печать шапки таблицы
	virtual void printTableHeader(PrintableTable* table) = 0;


private:

};




