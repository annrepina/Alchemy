#pragma once
#include "Formatting.h"

#define Y_COORD_FOR_PRINTING		10		// ���������� Y ��� ������

#define OUTER_BORDERS			2		// ������� ������� ������� (����� � ������)

// �����-������ ���������� ���-����
template <typename PrintableTable>
class TablePrinter
{
public:

	TablePrinter()
	{
		this->numberOfColumns = 0;
		this->numberOfLines = 0;
		this->tableWidth = 0;
		this->xCoordForPrinting = 0;
		this->yCoordForPrinting = Y_COORD_FOR_PRINTING;
	}

	virtual ~TablePrinter()
	{

	}

	virtual void print(PrintableTable* table)
	{
		//cout << "\x1b[3;9000r";

		this->columnWidthValues = calculateColumnWidth(table);

		this->tableWidth = calculateWidth(table);

		this->xCoordForPrinting = calculateXCoordForPrinting();

		this->numberOfColumns = this->columnWidthValues.size();

		this->numberOfLines = calculateNumberOfLines(table); 

		HANDLE hStdout;

		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

		SMALL_RECT srctScrollRect, srctClipRect;

		CHAR_INFO chiFill;

		COORD coordDest;

		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		GetConsoleScreenBufferInfo(hStdout, &csbiInfo);

		srctScrollRect.Top = csbiInfo.dwSize.Y - 16;

		srctScrollRect.Bottom = csbiInfo.dwSize.Y - 1;

		srctScrollRect.Left = 0;

		srctScrollRect.Right = csbiInfo.dwSize.X - 1;

		coordDest.X = 0;

		coordDest.Y = csbiInfo.dwSize.Y - 17;

		srctClipRect = srctScrollRect;

		chiFill.Attributes = BACKGROUND_GREEN | FOREGROUND_RED;

		chiFill.Char.UnicodeChar = ' ';

		ScrollConsoleScreenBuffer(

			hStdout,         // screen buffer handle

			&srctScrollRect, // scrolling rectangle

			&srctClipRect,   // clipping rectangle

			coordDest,       // top left destination cell

			& chiFill);       // fill character and color

		printHeader(table);
		
		printInnerFrame();
	}

protected:

	// ���������� Y ��� ������
	int yCoordForPrinting;

	// ���������� X ��� ������
	int xCoordForPrinting;

	// ����� �������
	int tableWidth;

	// ���-�� ��������
	int numberOfColumns;

	// ���-�� �����
	int numberOfLines;

	// ������ � ������� ������� �������
	vector<int> columnWidthValues;

#pragma region ������ �������

	// ���������� ���-�� ����� � �������
	virtual int calculateNumberOfLines(PrintableTable* table) = 0;

	virtual int calculateWidth(PrintableTable* table) = 0;

	virtual int calculateMaxIdStrSize(PrintableTable* table) = 0;

	virtual int calculateMaxNameSize(PrintableTable* table) = 0;

	// ����������� ������ ������� ������� � ���������� ������
	virtual vector<int> calculateColumnWidth(PrintableTable* table) = 0;

	virtual int calculateXCoordForPrinting()
	{
		/*this->xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);*/

		int xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);

		return xCoordForPrinting;
	}

#pragma endregion ������ �������

	// ������ ����� �������
	virtual void printHeader(PrintableTable* table) 
	{
		// ���������� ��� ������ ��������
		int xCoord = calculateXCoordInMiddle(table->getTitle());

		// ������� �� ����������� � ��������� Y
		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

		// �������� ������� ������� �������
		printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);

		cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);

		cout << VERTICAL_LINE;

		// ���������� ��� ������ �������� ����
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
			// ���� ������ ������
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

	// �������� ���������� ����� �������
	virtual void printInnerFrame()
	{
		// �� ���-�� �������
		for (int i = 0; i < this->numberOfLines; ++i)
		{
			//goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

			printInnerVerticalLines();

			cout << endl;

			//goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

			if (i == this->numberOfLines - 1)
			{
				printLowerTableFrame(this->columnWidthValues);
			}
			else 
				printInnerTableFrame(this->columnWidthValues);

			cout << endl;

			//cout << "\x1b[1T";
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

	//// �������� ������ ����� �������
	//void printLowerTableFrame()
	//{
	//	cout << turnOnDECMode();

	//	cout << LOWER_LEFT_CORNER;

	//	for (int j = 0; j < numberOfColumns; ++j)
	//	{
	//		for (int i = 0; i < this->columnWidthValues[j]; ++i)
	//		{
	//			cout << HORIZONTAL_LINE;
	//		}

	//		if ((numberOfColumns - 1) != j)
	//		{
	//			cout << SYMBOL_TURNED_T_WORD;
	//		}
	//		else
	//		{
	//			cout << LOWER_RIGHT_CORNER;
	//		}
	//	}

	//	cout << turnOffDECMode();
	//}

};




