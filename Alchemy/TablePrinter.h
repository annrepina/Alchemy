#pragma once
#include "Formatting.h"
//#include "Table.h"

#define Y_COORD_FOR_FRAME_PRINTING			12		// ���������� Y ��� ������ ����� ������� 
#define Y_COORD_FOR_HEADER_PRINTING			15		// ���������� Y ��� ������ ����� �������
#define Y_COORD_FOR_CONTENT_PRINTING		17		// ���������� Y ��� ������ ����������� �������


#define OUTER_BORDERS				2		// ������� ������� ������� (����� � ������)

#define NUMBER_OF_LINES_ON_PAGE		11		// ���-�� ����� �� ����� ��������
#define NUMBER_OF_CONTENT_LINES		10		// ���-�� ����� � ����������

#define GAPS						2		// ���-�� �������� � ������� (1 ����� � 1 ������)


// �����-������ ���������� ���-����
template <typename PrintableTable>
class TablePrinter
{
public:

	TablePrinter()
	{
		this->table = nullptr;
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

	virtual void print(int page)
	{
		setPage(page);

		printTitle();
		
		printInnerFrame();
	}

	// ��������� ������ �� �������
	virtual void calculateData()
	{
		this->numberOfLines = calculateNumberOfLines();

		this->columnWidthValues = calculateColumnWidth();

		this->tableWidth = calculateWidth();

		this->xCoordForFramePrinting = calculateXCoordForPrinting();

		this->numberOfColumns = this->columnWidthValues.size();

		this->xCoordsForContentPrinting = calculateXCoordsForContentPrinting();
	}

	// �������� ���-�� �������
	int getNumberOfColumns()
	{
		return this->numberOfColumns;
	}

	// �������� ���=�� �����
	int getNumberOfLines()
	{
		return this->numberOfLines;
	}

	// ������ �������
	virtual void setTable(PrintableTable* table)
	{
		this->table = table;
	}

protected:

	// ���������� �������
	PrintableTable* table;

	// ���������� Y ��� ������ ����� �������
	int yCoordForFramePrinting;

	// Y ���������� ��� ������ ����������� �������
	int yCoordForContentPrinting;

	// ���������� X ��� ������ ����� �������
	int xCoordForFramePrinting;

	// � ���������� ��� ������ ����������� �������
	int xCoordForContentPrinting;

	// ������ ��������� � ��� ������ ����������� �������
	vector<int> xCoordsForContentPrinting;

	// ����� �������
	int tableWidth;

	// ���-�� ��������
	int numberOfColumns;

	// ���-�� �����
	int numberOfLines;

	// �������� �������
	int page;

	// ������ � ������� ������� �������
	vector<int> columnWidthValues;

	// ������ �������� � ���������� �������
	vector< vector <string> > tableContent;

#pragma region ������ �������

	// ���������� ���-�� ����� � �������
	virtual int calculateNumberOfLines() = 0;

	virtual int calculateWidth() = 0;

	virtual int calculateMaxId() = 0;

	//virtual int calculateMaxIdStrSize() = 0;

	virtual int calculateMaxNameSize() = 0;

	// ������� ���������� ���-�� ���������
	virtual int calculateMaxNumberStrSize() = 0;

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

	// ����������� ������ ������� ������� � ���������� ������
	virtual vector<int> calculateColumnWidth() = 0;

	virtual int calculateXCoordForPrinting()
	{
		/*this->xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);*/

		int xCoordForPrinting = calculateXCoordInMiddle(this->tableWidth);

		return xCoordForPrinting;
	}



#pragma endregion ������ �������

	// ��������� ������ � ���������� �������
	virtual void fillInTableContent() = 0;

	// ������ �������� �������
	virtual void printTitle() 
	{
		// ���������� ��� ������ ��������
		int xCoord = calculateXCoordInMiddle(table->getTitle());

		// ������� �� ����������� � ��������� Y
		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

		// �������� ������� ������� �������
		printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);

		cout << goToXY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

		cout << VERTICAL_LINE;

		// ���������� ��� ������ �������� ����
		cout << goToXY(this->yCoordForFramePrinting, xCoord);

		cout << table->getTitle();

		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting + this->tableWidth - 1);

		cout << VERTICAL_LINE;

		goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

		printLowerLineOfHeader();

		//printLowerTableFrame(1, this->tableWidth - OUTER_BORDERS);
	}

	virtual void printLowerLineOfHeader()
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
		//// ���� ������� ��� ����� �������
		//int numberOfLines = this->numberOfLines + 1;

		// �� ���-�� �������
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

		// �������� ���������� Y
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

	// ������ ����������� ������� �� ���������
	virtual void printContent(int page) = 0;

	// ������ ����� �������
	virtual void printHeader() = 0;

private:

	void setPage(int page)
	{
		this->page = page;
	}

	// �������� ���������� �������� �������
	void clearTableContent()
	{
		for (auto strVector : this->tableContent)
		{
			delete strVector;
		}
	}
};
