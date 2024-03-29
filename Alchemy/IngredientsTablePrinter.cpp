#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
	numberOfAvailableContent = 0;
}

IngredientsTablePrinter::~IngredientsTablePrinter()
{
}

#pragma region ������ �������

int IngredientsTablePrinter::calculateNumberOfLines()
{
	// ���-�� ����� ����� ���-�� ������������
	int numberOfLines = (--table->getEndIterator())->first;

	return numberOfLines;
}

int IngredientsTablePrinter::calculateWidth()
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	return totalWidth;
}

int IngredientsTablePrinter::calculateMaxId()
{
	// ��������� id
	int maxId = (--table->getEndIterator())->first;

	maxId = to_string(maxId).size();

	return maxId;
}

int IngredientsTablePrinter::calculateMaxNameSize()
{
	// ����������� ������ �������� ������� ������ ����� ������� ����������� � map
	int maxNameSize = table->getStartIterator()->second->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();
	map<int, Ingredient*>::iterator endIter = table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ����������� ������ ����� �������� ��������
		int size = i->second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize()
{
	// ��� ���-�� ������������
	int maxNumber = table->getStartIterator()->second->getNumber();

	// ��� ���-�� ������������ � ���� ������
	string strMaxNumber;

	// ������ ������ ��� ���-�� ������������ 
	int strMaxNumberSize;

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();
	map<int, Ingredient*>::iterator endIter = table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ����������� ���-�� �������� ��������
		int number = i->second->getNumber();

		if (maxNumber < number)
			maxNumber = number;
	}

	strMaxNumber = to_string(maxNumber);

	strMaxNumberSize = strMaxNumber.size();

	if (strMaxNumberSize > NUMBER_LENGTH)
		return strMaxNumberSize;

	else
		return NUMBER_LENGTH;
}

int IngredientsTablePrinter::calculateMaxEffectNameSize()
{
	// �������� �� map 
	map<int, bool>::iterator firstIter = table->getStartIterator()->second->getBeginIteratorOfEffectsId();

	// Id-���� ������� �������� map
	int firstEffectId = firstIter->first;

	int maxEffectNameSize = table->getEffectsTable()->getEffectByKey(firstEffectId)->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();
	map<int, Ingredient*>::iterator endIter = table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ��� ������� ����������� ������� ���� �������� �� map �� ��������, ����������� �� 1�� �������
		map<int, bool>::iterator effectIter = i->second->getBeginIteratorOfEffectsId();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++effectIter)
		{
			// Id ������� �������� ����������� �� ����� ���������
			int id = effectIter->first;

			// ����������� ����� ����� ������� � ������� id 
			int effectNameSize = table->getEffectsTable()->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}

vector<int> IngredientsTablePrinter::calculateColumnWidth()
{
	// �������� ����� �������
	vector <int> columnWidth;

	// ������� ������ ������� � id
	int idColumnWidth = calculateMaxId() + GAPS;

	// ��������� ������ ������� � id
	columnWidth.push_back(idColumnWidth);

	// ������� ������ ������� � ������
	int nameColumnWidth = calculateMaxNameSize() + GAPS;

	// ��������� ������ ������� � ������
	columnWidth.push_back(nameColumnWidth);

	// ������� ������ ������� � �����
	int priceColumnWidth = PRICE_LENGTH + GAPS;

	columnWidth.push_back(priceColumnWidth);

	int effectColumnWidth = calculateMaxEffectNameSize() + GAPS;
	
	// ��������� ������ � ������ ������� ���, ������� ��������
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		columnWidth.push_back(effectColumnWidth);
	}

	int numberColumnWidth = calculateMaxNumberStrSize() + GAPS;

	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

int IngredientsTablePrinter::calculateNumberOfAvailableElements()
{
	int numberOfAvailableElements = 0;

	for (int i = 0; i < this->numberOfLines ; ++i)
	{
		// ���� ���-�� ����������� ������ ����
		if (this->table->getIngredientById(i + 1)->getNumber() > 0)
		{
			++numberOfAvailableElements;
		}
	}

	return numberOfAvailableElements;
}

void IngredientsTablePrinter::calculateData()
{
	TablePrinter::calculateData();

	this->numberOfAvailableContent = calculateNumberOfAvailableElements();
}

int IngredientsTablePrinter::getNumberOfAvailableContent()
{
	return this->numberOfAvailableContent;
}

#pragma endregion ������ �������

#pragma region ������ ������

void IngredientsTablePrinter::print(int page)
{
	TablePrinter::print(page);

	this->printHeader();

	this->printContent(page);
}

void IngredientsTablePrinter::print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting)
{
	TablePrinter::print(page);

	this->printHeader(numberOfColumn, orderOfSorting);

	this->printContent(content, page);
}

void IngredientsTablePrinter::printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting)
{
	TablePrinter::print(page);

	this->printHeader(numberOfColumn, orderOfSorting);

	this->printContent(page);
}

void IngredientsTablePrinter::printAvailableElements(int page)
{
	TablePrinter::print(page);

	this->printHeader();

	this->printAvailableContent(page);
}

void IngredientsTablePrinter::printHeader()
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "�", "���", "����", "������ 1", "������ 2", "���-��" };

	this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	for (int i = 0; i < this->numberOfColumns; ++i)
	{
		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << namesOfColumns[i];
	}
}

void IngredientsTablePrinter::printHeader(int numberOfColumn, bool ordreOfSorting)
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "�", "���", "����", "������ 1", "������ 2", "���-��" };

	this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	// �������� 1 �.�. ��������� � ����
	numberOfColumn -= 1;

	for (int i = 0; i < this->numberOfColumns; ++i)
	{
		if (numberOfColumn == i)
		{
			string sortingSymbol = " ";

			if (ordreOfSorting == ASCENDING_ORDER_OF_SORTING)
				sortingSymbol = "^";

			else
				sortingSymbol = "v";

			cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i] - 1);

			printColoredText(sortingSymbol, R_DECIMAL_YELLOW, G_DECIMAL_YELLOW, B_DECIMAL_YELLOW);
		}

		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << namesOfColumns[i];
	}
}

void IngredientsTablePrinter::printContent(int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// ���������� ����������
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

	int i = 0;

	if (page > 1)
	{
		i = (page - 1) * NUMBER_OF_CONTENT_LINES;
	}

	for (; i < this->numberOfLines && i < border; ++i)
	{
		for (int j = 0; j < this->numberOfColumns; ++j)
		{
			cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[j]);

			cout << this->tableContent[i][j];
		}

		this->yCoordForContentPrinting += GAPS;
	}

	cout << endl << endl;
}

void IngredientsTablePrinter::printContent(vector<vector<string>> content, int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// ���������� ����������
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

	int i = 0;

	int size = content.size();

	if (page > 1)
	{
		i = (page - 1) * NUMBER_OF_CONTENT_LINES;
	}

	for (; i < size && i < border; ++i)
	{
		for (int j = 0; j < this->numberOfColumns; ++j)
		{
			cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[j]);

			cout << content[i][j];
		}

		this->yCoordForContentPrinting += GAPS;
	}

	cout << endl << endl;
}

void IngredientsTablePrinter::printAvailableContent(int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// ���������� ����������
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

	int i = 0;

	auto beginIterOfAvailableElements = this->table->getBeginIteratorOfAvailableElements();
	auto endIterOfAvailableElements = this->table->getEndIteratorOfAvailableElements();

	if (page > 1)
	{
		i = (page - 1) * NUMBER_OF_CONTENT_LINES;
	}

	auto startIter = beginIterOfAvailableElements + i;

	for (auto j = startIter; i < this->numberOfLines && i < border && j != endIterOfAvailableElements; ++i, ++j)
	{
		int index = *j;

		for (int k = 0; k < this->numberOfColumns; ++k)
		{
			cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[k]);

			cout << this->tableContent[index - 1][k];
		}

		this->yCoordForContentPrinting += GAPS;
	}

	cout << endl << endl;
}

#pragma endregion ������ ������

void IngredientsTablePrinter::fillInTableContent()
{
	// �������� �� ������ map � �������
	map<int, Ingredient*>::iterator iter = table->getStartIterator();

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// id ������� �����������
	int effectId;

	// �������� �� ������ ������ ������� �����������
	bool isEffectKnown;

	for (int i = 0; i < this->numberOfLines; ++i)
	{
		// ������� ���������� ������
		vector <string> line;

		// ��������� ���� ������ �� �������
		this->tableContent.push_back(line);

		// �������� id
		intValue = iter->first;

		// ��������� � ������ ������ id
		this->tableContent[i].push_back(to_string(intValue));

		// �������� ���
		strValue = iter->second->getName();

		// ��������� � ������ ������ ���
		this->tableContent[i].push_back(strValue);

		// �������� ����
		intValue = iter->second->getPrice();

		// ��������� ���� 
		this->tableContent[i].push_back(to_string(intValue));

		// �������� �� map � ��������� � �����������
		map<int, bool>::iterator effectIter = iter->second->getBeginIteratorOfEffectsId();

		// ��� ������� �����������
		for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
		{
			// �������� ������
			isEffectKnown = effectIter->second;

			// ��� �������
			string effectName;

			// ���� ��� ������ ��������
			if (isEffectKnown)
			{
				// ����������� id
				effectId = effectIter->first;

				// ����������� ���
				effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
			}
			else
				effectName = UNKNOWN_EFFECT;

			// ��������� ��� ������� 
			this->tableContent[i].push_back(effectName);

			++effectIter;
		}

		intValue = iter->second->getNumber();

		// ��������� ���-�� �����������
		this->tableContent[i].push_back(to_string(intValue));

		// ����������� ��������
		++iter;
	}
}

void IngredientsTablePrinter::changeTableContentForOneElement(int id)
{
	// ������� ������ �������
	this->tableContent[id - 1].clear();

	// Id ��� �������� �������
	int tableContentId = id - 1;

	Ingredient* ingredient = table->getIngredientById(id);

	// �������� �� ������ ������ ������� �����������
	bool isEffectKnown;

	// ����� ��������
	int intValue;

	// id ������� �����������
	int effectId;

	// ��������� ��������
	string strValue;

	// ��������� � ������ id
	this->tableContent[tableContentId].push_back(to_string(id));

	// ��������� ��������
	strValue = ingredient->getName();

	// ��������� ���
	this->tableContent[tableContentId].push_back(strValue);

	intValue = ingredient->getPrice();

	this->tableContent[tableContentId].push_back(to_string(intValue));

	// �������� �� map � ��������� � �����������
	map<int, bool>::iterator effectIter = ingredient->getBeginIteratorOfEffectsId();

	// ��� ������� �����������
	for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
	{
		// �������� ������
		isEffectKnown = effectIter->second;

		// ��� �������
		string effectName;

		// ���� ��� ������ ��������
		if (isEffectKnown)
		{
			// ����������� id
			effectId = effectIter->first;

			// ����������� ���
			effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
		}
		else
			effectName = UNKNOWN_EFFECT;

		// ��������� ��� ������� 
		this->tableContent[tableContentId].push_back(effectName);

		++effectIter;
	}

	intValue = ingredient->getNumber();

	this->tableContent[tableContentId].push_back(to_string(intValue));

	// ������������� ������
	this->calculateData();
}

void IngredientsTablePrinter::changeTableContentForOneElement(int id, int previousNumber)
{
	Ingredient* ingredient = table->getIngredientById(id);

	// ���� ���������� ���-�� ����� ���� � ������� ���-�� ������ ����
	if (previousNumber == 0 && ingredient->getNumber() > 0)
		++numberOfAvailableContent;

	// ���� ���������� ���� ������ ����, � ������ ����
	else if (previousNumber > 0 && ingredient->getNumber() == 0)
		--numberOfAvailableContent;

	changeTableContentForOneElement(id);
}

void IngredientsTablePrinter::addElementToTableContent(int id)
{
	// �������� �� ����� map � �������
	map<int, Ingredient*>::iterator endIter = --table->getEndIterator();

	// ��������� ������ � ���������� ������� ����� ���������� id � �������
	int lastId = endIter->first - 1;

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// id ������� �����������
	int effectId;

	// �������� �� ������ ������ ������� �����������
	bool isEffectKnown;

	// ������� ���������� ������
	vector <string> line;

	// ��������� ���� ������ �� �������
	this->tableContent.push_back(line);

	// �������� id
	intValue = endIter->first;

	// ��������� � ������ ������ id
	tableContent[lastId].push_back(to_string(intValue));

	// �������� ���
	strValue = endIter->second->getName();

	// ��������� � ������ ���
	this->tableContent[lastId].push_back(strValue);

	// �������� ����
	intValue = endIter->second->getPrice();

	// ��������� ���� 
	this->tableContent[lastId].push_back(to_string(intValue));

	// ��� ������� �����������
	for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
	{
		// �������� �� map � ��������� � �����������
		map<int, bool>::iterator effectIter = endIter->second->getBeginIteratorOfEffectsId();

		// �������� ������
		isEffectKnown = effectIter->second;

		// ��� �������
		string effectName;

		// ���� ��� ������ ��������
		if (isEffectKnown)
		{
			// ����������� id
			effectId = effectIter->first;

			// ����������� ���
			effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
		}
		else
			effectName = UNKNOWN_EFFECT;

		// ��������� ��� ������� 
		this->tableContent[lastId].push_back(effectName);

		++effectIter;
	}

	intValue = endIter->second->getNumber();

	// ��������� ���-�� �����������
	this->tableContent[lastId].push_back(to_string(intValue));

	// ������������� ������
	this->calculateData();
}
