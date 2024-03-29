#pragma once
#include "Formatting.h"
#include "IObserver.h"

// ���������� ��� ������
#define Y_COORD_FOR_FRAME_PRINTING			19		// ���������� Y ��� ������ ����� ������� 
#define Y_COORD_FOR_HEADER_PRINTING			22		// ���������� Y ��� ������ ����� �������
#define Y_COORD_FOR_CONTENT_PRINTING		24		// ���������� Y ��� ������ ����������� �������

#define OUTER_BORDERS						2		// ������� ������� ������� (����� � ������)

#define NUMBER_OF_LINES_ON_PAGE				11		// ���-�� ����� �� ����� ��������
#define NUMBER_OF_CONTENT_LINES				10		// ���-�� ����� � ����������

#define GAPS								2		// ���-�� �������� � ������� (1 ����� � 1 ������)

#define ASCENDING_ORDER_OF_SORTING			true	// ������� ���������� �� �����������
#define DESCENDING_ORDER_OF_SORTING			false	// ������� ���������� �� ��������

// �����-������ ���������� ������� - �������
template <typename PrintableTable>
class TablePrinter : public IObserver
{
public:

	// ����������� �� ���������
	TablePrinter()
	{
		this->table = nullptr;
		this->numberOfColumns = 0;
		this->numberOfLines = 0;
		this->numberOfAvailableContent = 0;
		this->tableWidth = 0;
		this->xCoordForFramePrinting = 0;
		this->xCoordForContentPrinting = 0;
		this->yCoordForFramePrinting = Y_COORD_FOR_FRAME_PRINTING;
		this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;
		this->page = 1;
	}

	// ����������
	virtual ~TablePrinter()
	{

	}

	// �������� ������� ��� ������ ������ �� ��������� ������� �������� - �������
	void update(int id, bool isNewElement) override
	{
		// ���� ����� �������
		if (isNewElement)
		{
			addElementToTableContent(id);
		}
		else
		{
			//this->tableContent[id - 1].clear();

			changeTableContentForOneElement(id);
		}
	}

	// �������� ������� ��� ������ ������ �� ��������� ������� �������� - �������
	void update(int id, int previousNumber) override
	{
		// ���� ��������� ������, ��� id, ������ ��� �������� ����� �������
		if (this->tableContent.size() < id)
		{
			addElementToTableContent(id);
		}
		else
		{
			this->tableContent[id - 1].clear();

			changeTableContentForOneElement(id, previousNumber);
		}
	}

	// �������� ������� ��� ������ ������ �� ��������� ������� �������� - �������
	virtual void update()
	{

	}

	// ����� ������ ������ � �������� �������
	virtual void print(int page)
	{
		setPage(page);

		printTitle();
		
		printInnerFrame();
	}

	// ������ ������������� �������� �������� ������������� ��������
	virtual void print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting) = 0;

	// ������ ������� � ��������� ����������
	virtual void printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting) = 0;
	
	// ������ ��������� �������, ������� �������� ��������, �.�. � ������� ���-�� ������ ����
	virtual void printAvailableElements(int page) = 0;

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

	// �������� ������� �������
	vector<vector<string>> getTableContent()
	{
		return this->tableContent;
	}

	// �������� �������
	PrintableTable* getTable()
	{
		return this->table;
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

	// ���-�� ���������� ��������
	int numberOfAvailableContent;

#pragma region ������ �������

	// ���������� ���-�� ����� � �������
	virtual int calculateNumberOfLines() = 0;

	// ��������� ������ �������
	virtual int calculateWidth() = 0;

	// ��������� ������ ����� - ������������� id �������� � �������
	virtual int calculateMaxId() = 0;

	// ��������� ������ ������������� ����� �������� � �������
	virtual int calculateMaxNameSize() = 0;

	// ������� ������ ����� - ���������� ���-�� ������� ����� ��������
	virtual int calculateMaxNumberStrSize() = 0;

	// ��������� ���������� X ��� ������ �������� �������
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

	// ����������� ���������� x ��� ������ �������
	virtual int calculateXCoordForPrinting()
	{
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
	}

	// ������ ������ ����� ����� �������
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
		// �� ���-�� �������
		for (int i = 0; i < NUMBER_OF_LINES_ON_PAGE; ++i)
		{
			goToCoordAndIncreaseY(this->yCoordForFramePrinting, this->xCoordForFramePrinting);

			printInnerVerticalLines();

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

	// ������ ���������� ������������ ����� ������
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

	// ������ ��������, ������������� �������� ��������
	virtual void printContent(vector<vector<string>> content, int page) = 0;

	// ������ ��������� ������������ ������� (��������, � ������� ���-�� ������ ����)
	virtual void printAvailableContent(int page) = 0;

	// ������ ����� �������
	virtual void printHeader() = 0;

	// ������ ����� � ��������� ����������
	virtual void printHeader(int numberOfColumn, bool ordreOfSorting) = 0;

	// �������� ������� � �������
	virtual void addElementToTableContent(int id) = 0;

	// �������� ������� ������ ��������
	virtual void changeTableContentForOneElement(int id) = 0;

	// �������� ������� ������ �������� � ������ ������� ���-�� ����� ��������
	virtual void changeTableContentForOneElement(int id, int previousNumber) = 0;

private:

	// ������ ��� ��������
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