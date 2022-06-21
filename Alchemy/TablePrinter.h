#pragma once
#include "Formatting.h"

#define Y_COORD_FOR_FRAME_PRINTING			11		// Координата Y для печати рамки таблицы 
#define Y_COORD_FOR_HEADER_PRINTING			14		// Координата Y для печати шапки таблицы
#define Y_COORD_FOR_CONTENT_PRINTING		16		// Координата Y для печати содержимого таблицы


#define OUTER_BORDERS				2		// Внешние границы таблицы (левая и правая)

#define NUMBER_OF_LINES_ON_PAGE		11		// Кол-во строк на одной странице
#define NUMBER_OF_CONTENT_LINES		10		// Кол-во строк с содержимым
#define NUMBER_OF_COLUMNS			6		// Кол-во колонок

#define GAPS						2		// Кол-во пробелов в столбце (1 слева и 1 справа)


// Класс-шаблон печатающий что-либо
template <typename PrintableTable>
class TablePrinter
{
public:

	TablePrinter()
	{
		this->numberOfColumns = 0;
		this->numberOfLines = 0;
		this->tableWidth = 0;
		this->xCoordForFramePrinting = 0;
		this->xCoordForContentPrinting = 0;
		this->yCoordForFramePrinting = Y_COORD_FOR_FRAME_PRINTING;
		this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;
		this->page = 1;
	}

	virtual ~TablePrinter()
	{

	}

	virtual void print(PrintableTable* table, int page)
	{
		//cout << "\x1b[3;9000r";

		setPage(page);

		this->columnWidthValues = calculateColumnWidth(table);

		this->tableWidth = calculateWidth(table);

		this->xCoordForFramePrinting = calculateXCoordForPrinting();

		this->numberOfColumns = this->columnWidthValues.size();

		this->numberOfLines = calculateNumberOfLines(table); 

		this->xCoordsForContentPrinting = calculateXCoordsForContentPrinting();

		printTitle(table);
		
		printInnerFrame();


	}

	// Получить кол-во колонок
	int getNumberOfColumns()
	{
		return this->numberOfColumns;
	}

	// Получить кол=во строк
	int getNumberOfLines()
	{
		return this->numberOfLines;
	}

protected:

	// Координата Y для печати рамки таблицы
	int yCoordForFramePrinting;

	// Y координата для печати содержимого таблицы
	int yCoordForContentPrinting;

	// Координата X для печати рамки таблицы
	int xCoordForFramePrinting;

	// Х координата для печати содержимого таблицы
	int xCoordForContentPrinting;

	// Вектор координат х для печати содержимого таблицы
	vector<int> xCoordsForContentPrinting;

	// Длина таблицы
	int tableWidth;

	// Кол-во столбцов
	int numberOfColumns;

	// Кол-во строк
	int numberOfLines;

	// Страница таблицы
	int page;

	// Вектор с шириной каждого столбца
	vector<int> columnWidthValues;

	// Вектор стрингов с содержимым таблицы
	vector< vector <string> > tableContent;

#pragma region МЕТОДЫ РАСЧЕТА

	// Рассчитать кол-во строк в таблице
	virtual int calculateNumberOfLines(PrintableTable* table) = 0;

	virtual int calculateWidth(PrintableTable* table) = 0;

	virtual int calculateMaxId(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	virtual vector<int> calculateXCoordsForContentPrinting()
	{
		int startCoord = xCoordForFramePrinting + GAPS; 

		vector <int> coords;

		coords.push_back(startCoord);

		for (int i = 1; i < this->numberOfColumns; ++i)
		{
			startCoord += this->columnWidthValues[i - 1] /*- GAPS) + GAPS */ + 1;
			coords.push_back(startCoord);
		}

		return coords;
	}

	// Расчитывает ширину каждого столбца и возвращает вектор
	virtual vector<int> calculateColumnWidth(PrintableTable* table) = 0;

	virtual int calculateXCoordForPrinting()
	{
		/*this->xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);*/

		int xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);

		return xCoordForPrinting;
	}

	// заполнить вектор с содержимым таблицы
	virtual void fillInTableContent(PrintableTable* table) = 0;

#pragma endregion МЕТОДЫ РАСЧЕТА

	// Печать названия таблицы
	virtual void printTitle(PrintableTable* table) 
	{
		// Координата для печати названия
		int xCoord = calculateXCoordInMiddle(table->getTitle());

		// Перейти по координатам и увеличить Y
		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

		// Печатаем верхнюю границу таблицы
		printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);

		cout << goToXY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

		cout << VERTICAL_LINE;

		// Координаты для печати названия табл
		cout << goToXY(this->yCoordForFramePrinting, xCoord);

		cout << table->getTitle();

		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting + this->tableWidth - 1);

		cout << VERTICAL_LINE;

		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

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
		//// Одна колонка для шапки таблицы
		//int numberOfLines = this->numberOfLines + 1;

		// По кол-ву колонок
		for (int i = 0; i < NUMBER_OF_LINES_ON_PAGE; ++i)
		{
			goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

			printInnerVerticalLines();

			//cout << endl;

			goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

			if (i == NUMBER_OF_LINES_ON_PAGE - 1)
			{
				printLowerTableFrame(this->columnWidthValues);
			}
			else 
				printInnerTableFrame(this->columnWidthValues);
		}

		// Обнуляем координату Y
		this->yCoordForFramePrinting = Y_COORD_FOR_FRAME_PRINTING;
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

	// Печать содержимого таблицы по страницам
	virtual void printContent(PrintableTable* table, int page) = 0;

	// Печать шапки таблицы
	virtual void printHeader() = 0;

private:

	void setPage(int page)
	{
		this->page = page;
	}
};
