#pragma once
#include "Formatting.h"

#define Y_COORD_FOR_PRINTING		10		// Координата Y для печати

#define OUTER_BORDERS			2		// Внешние границы таблицы (левая и правая)

// Класс-шаблон печатающий что-либо
template <typename PrintableTable>
class TablePrinter
{
public:

	TablePrinter()
	{
		this->numberOfColumns = 0;
		this->numberOfLines = 5;
		this->tableWidth = 0;
		this->xCoordForPrinting = 0;
		this->yCoordForPrinting = Y_COORD_FOR_PRINTING;
	}

	virtual ~TablePrinter()
	{

	}

	virtual void print(PrintableTable* table)
	{
		this->columnWidthValues = calculateColumnWidth(table);

		this->tableWidth = calculateWidth(table);

		this->xCoordForPrinting = calculateXCoordForPrinting();

		this->numberOfColumns = this->columnWidthValues.size();

		printHeader(table);
		
		printInnerFrame();
	}

protected:

	// Координата Y для печати
	int yCoordForPrinting;

	// Координата X для печати
	int xCoordForPrinting;

	// Длина таблицы
	int tableWidth;

	// Кол-во столбцов
	int numberOfColumns;

	// Кол-во строк
	int numberOfLines;

	// Вектор с шириной каждого столбца
	vector<int> columnWidthValues;

#pragma region МЕТОДЫ РАСЧЕТА

	virtual int calculateWidth(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	// Расчитывает ширину каждого столбца и возвращает вектор
	virtual vector<int> calculateColumnWidth(PrintableTable* table) = 0;

	virtual int calculateXCoordForPrinting()
	{
		/*this->xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);*/

		int xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);

		return xCoordForPrinting;
	}

#pragma endregion МЕТОДЫ РАСЧЕТА

	// Печать шапки таблицы
	virtual void printHeader(PrintableTable* table) 
	{
		// Координата для печати названия
		int xCoord = calculateXCoordInMiddle(table->getTitle());

		// Перейти по координатам и увеличить Y
		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

		// Печатаем верхнюю границу таблицы
		printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);

		cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);

		cout << VERTICAL_LINE;

		// Координаты для печати названия табл
		cout << goToXY(this->yCoordForPrinting, xCoord);

		cout << table->getTitle();

		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting + this->tableWidth - 1);

		cout << VERTICAL_LINE;

		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

		printLowerLineOfHeader(table);

		//printLowerTableFrame(1, this->tableWidth - OUTER_BORDERS);
	}

	virtual void printLowerLineOfHeader(PrintableTable* table)
	{
		cout << turnOnDECMode();

		for (int j = 0; j < numberOfColumns; ++j)
		{
			// если первый индекс
			if (j == FIRST_INDEX)
				cout << SYMBOL_FIRST_HALF_H_LETTER;

			else
				cout << SYMBOL_T_WORD;

			for (int i = 0; i < columnWidthValues[j]; ++i)
			{
				cout << HORIZONTAL_LINE;
			}
		}

		cout << SYMBOL_SECOND_HALF_H_LETTER << turnOffDECMode();
	}

	// Печатать внутреннюю рамку таблицы
	virtual void printInnerFrame()
	{
		// По кол-ву колонок
		for (int i = 0; i < this->numberOfLines; ++i)
		{
			goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

			printInnerTableFrame(this->columnWidthValues);

			goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

			printInnerVerticalLines();
		}
	}

	virtual void printInnerVerticalLines()
	{
		cout << turnOnDECMode();

		for (int i = 0; i < numberOfColumns; ++i)
		{
			cout << VERTICAL_LINE;

			for (int j = 0; j < this->columnWidthValues[i]; ++j)
			{
				cout << ' ';
			}
		}

		cout << VERTICAL_LINE << turnOffDECMode();
	}

private:



};




