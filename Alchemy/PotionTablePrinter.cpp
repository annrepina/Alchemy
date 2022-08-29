#include "PotionTablePrinter.h"

PotionTablePrinter::PotionTablePrinter()
{
}

PotionTablePrinter::~PotionTablePrinter()
{
}

void PotionTablePrinter::print(int page)
{
	TablePrinter::print(page);

	this->printHeader();

	this->printContent(page);
}

void PotionTablePrinter::print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting)
{
}

void PotionTablePrinter::printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting)
{
	TablePrinter::print(page);

	this->printHeader(numberOfColumn, orderOfSorting);

	this->printContent(page);
}

void PotionTablePrinter::fillInTableContent()
{
	// �������� �� ������ map � �������
	auto startIter = table->getStartIterator();

	// �������� �� ����� map
	auto endIter = table->getEndIterator();

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// �������
	int counter = 0;

	for (auto i = startIter; i != endIter; ++i, ++counter)
	{
		// ������� ���������� ������
		vector <string> line;

		// ��������� ���� ������ �� �������
		this->tableContent.push_back(line);

		// �������� id
		intValue = i->first;

		// ��������� � ������ ������ id
		this->tableContent[counter].push_back(to_string(intValue));

		// id �������
		int effectId = i->second->getEffectId();

		// �������� ��� ����� 
		strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

		// ��������� � ������ ������ ���
		this->tableContent[counter].push_back(strValue);

		intValue = i->second->getPower();

		this->tableContent[counter].push_back(to_string(intValue));

		// �������� ����
		intValue = i->second->getPrice();

		// ��������� ���� 
		this->tableContent[counter].push_back(to_string(intValue));

		// �������� ���-��
		intValue = i->second->getNumber();

		// ��������� ���-�� �����������
		this->tableContent[counter].push_back(to_string(intValue));
	}
}

void PotionTablePrinter::printAvailableElements(int page)
{
}

void PotionTablePrinter::update()
{
	calculateData();
}

#pragma region ������ �������

int PotionTablePrinter::calculateNumberOfLines()
{
	// �������� �� ������ map
	auto startIter = table->getStartIterator();

	// �������� �� ����� map
	auto endIter = table->getEndIterator();

	// ���-�� �����
	int numberOfLines = 0;

	for (auto i = startIter; i != endIter; ++i)
	{
		//// ���� ���-�� ����� ������ 0
		//if (i->second->getNumber() > 0)
		//{
			++numberOfLines;
		//}
	}


	return numberOfLines;
}

vector<int> PotionTablePrinter::calculateColumnWidth()
{
	// �������� ����� �������
	vector <int> columnWidth;

	// ������� ������ ������� � ������� �����
	int idColumnWidth = calculateMaxId() + GAPS;

	// ��������� ������ ������� � id
	columnWidth.push_back(idColumnWidth);

	// ������� ������ ������� � ������
	int nameColumnWidth = calculateMaxNameSize() + GAPS;

	// ��������� ������ ������� � ������
	columnWidth.push_back(nameColumnWidth);

	int powerColumnWidth = calculateMaxPowerStrSize() + GAPS;

	// ��������� ������ ������� ��������
	columnWidth.push_back(powerColumnWidth);

	// ������� ������ ������� � �����
	int priceColumnWidth = calculateMaxPriceStrSize() + GAPS;

	columnWidth.push_back(priceColumnWidth);

	int numberColumnWidth = calculateMaxNumberStrSize() + GAPS;

	// ��������� ������ ������� � ���-���
	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

int PotionTablePrinter::calculateWidth()
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	return totalWidth;
}

int PotionTablePrinter::calculateMaxId()
{
	int maxIdSize = to_string(calculateNumberOfLines()).size();

	return maxIdSize;
}

int PotionTablePrinter::calculateMaxNameSize()
{
	auto startIter = this->table->getEffectsTable()->getStartIterator();

	auto endIter = this->table->getEffectsTable()->getEndIterator();

	// ����������� ������ �������� ������� ������ ����� ������� ������� � map
	int maxNameSize = startIter->second->getName().size();

	for (auto i = startIter; i != endIter; ++i)
	{
		// ����������� ������ ����� �������� ��������
		int size = i->second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int PotionTablePrinter::calculateMaxNumberStrSize()
{
	auto startIter = table->getStartIterator();

	auto endIter = table->getEndIterator();

	if (startIter != endIter)
	{
		// ��� ���-�� �����
		int maxNumber = startIter->second->getNumber();

		for (auto i = startIter; i != endIter; ++i)
		{
			// ����������� ���-�� �������� ��������
			int number = i->second->getNumber();

			if (maxNumber < number)
				maxNumber = number;
		}

		maxNumber = to_string(maxNumber).size();

		if (maxNumber > NUMBER_LENGTH)
			return maxNumber;

		else
			return NUMBER_LENGTH;
	}

	return 0;
}

int PotionTablePrinter::calculateMaxPowerStrSize()
{
	auto startIter = this->table->getStartIterator();
	auto endIter = this->table->getEndIterator();

	if (startIter != endIter)
	{
		int maxPower = startIter->second->getPower();

		for (auto i = startIter; i != endIter; ++i)
		{
			int power = i->second->getPower();

			if (maxPower < power)
				maxPower = power;
		}

		maxPower = to_string(maxPower).size();

		if (maxPower > POWER_LENGTH)
			return maxPower;

		else
			return POWER_LENGTH;
	}

	return 0;
}

int PotionTablePrinter::calculateMaxPriceStrSize()
{
	auto startIter = this->table->getStartIterator();
	auto endIter = this->table->getEndIterator();

	if (startIter != endIter)
	{
		int maxPrice = startIter->second->getPrice();

		for (auto i = startIter; i != endIter; ++i)
		{
			int price = i->second->getPrice();

			if (maxPrice < price)
				maxPrice = price;
		}

		maxPrice = to_string(maxPrice).size();

		if (maxPrice > PRICE_LENGTH)
			return maxPrice;

		else
			return PRICE_LENGTH;
	}

	return 0;
}

#pragma endregion ������ �������

void PotionTablePrinter::printHeader()
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "�", "���", "��������", "����", "���-��"};

	this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	for (int i = 0; i < this->numberOfColumns; ++i)
	{
		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << namesOfColumns[i];
	}
}

void PotionTablePrinter::printHeader(int numberOfColumn, bool ordreOfSorting)
{
	//string namesOfColumns[NUMBER_OF_COLUMNS] = { "�", "���", "��������", "����", "���-��" };

	//this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	//// ��������� �� 1, �.�. ��������� � ����
	//numberOfColumn -= 1;

	//for (int i = 0; i < this->numberOfColumns; ++i)
	//{
	//	//int xCoord = 0;

	//	if (i == numberOfColumn)
	//	{
	//		if(ordreOfSorting == ASC)
	//		printColoredTextByCoords()

	//		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i] - 1);
	//	}

	//	cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i] - 1);

	//	

	//	printColoredTextByCoords("^")

	//	cout << namesOfColumns[i];
	//}
}

void PotionTablePrinter::printContent(int page)
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

void PotionTablePrinter::printContent(vector<vector<string>> content, int page)
{
}

void PotionTablePrinter::printAvailableContent(int page)
{
}

void PotionTablePrinter::changeTableContentForOneElement(int id)
{
	int index = -1;

	string strIndex = to_string(id);

	int tableContentSize = this->tableContent.size();

	index = findIndexInTableContentByKey(id);

	// ������� ������ �������
	this->tableContent[index].clear();

	Potion* potion = table->getPotionById(id);

	if (potion->getNumber() == 0)
	{
		// �������� �� ������ � ����� ������� � ���������
		auto beginIter = this->tableContent.begin();
		auto endIter = this->tableContent.begin();

		// �������� �� ������ ������� � ���������� ������������ id
		auto beginIterOfAvailableContent = this->availableElementsId.begin();

		int startIndex = 0;

		// ���������� � ����� ������
		for (auto i = beginIter; i != endIter; ++i, ++startIndex, ++beginIterOfAvailableContent)
		{
			// ���� ���������� �������
			if (startIndex == index)
			{
				// �� ����������� ������� ��������
				beginIter = i;
				break;
			}
		}

		// ������� ������ ������� �� ������� �������� � ��������� id
		this->tableContent.erase(beginIter);
		this->availableElementsId.erase(beginIterOfAvailableContent);

		// ������������� ������
		this->calculateData();

		return;
	}

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// ��������� � ������ ������ id
	this->tableContent[index].push_back(to_string(id));

	// id �������
	int effectId = potion->getEffectId();

	// �������� ��� ����� 
	strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

	// ��������� � ������ ������ ���
	this->tableContent[index].push_back(strValue);

	intValue = potion->getPower();

	this->tableContent[index].push_back(to_string(intValue));

	// �������� ����
	intValue = potion->getPrice();

	// ��������� ���� 
	this->tableContent[index].push_back(to_string(intValue));

	// �������� ���-��
	intValue = potion->getNumber();

	// ��������� ���-�� �����������
	this->tableContent[index].push_back(to_string(intValue));

	// ������������� ������
	this->calculateData();
}

void PotionTablePrinter::changeTableContentForOneElement(int id, int previousNumber)
{
}

void PotionTablePrinter::addElementToTableContent(int id)
{
	this->availableElementsId.push_back(id);

	Potion* potion = table->getPotionById(id);

	//// ��������� ������ � ���������� ������� 
	//int lastIndex = findIndexInTableContentByKey(id);

	int lastIndex = tableContent.size();

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// id ������� �����������
	int effectId;

	// ������� ���������� ������
	vector <string> line;

	// ��������� ���� ������ �� �������
	this->tableContent.push_back(line);

	//// �������� id
	//intValue = endIter->first;

	// ��������� � ������ ������ id
	tableContent[lastIndex].push_back(to_string(id));

	// id �������
	effectId = potion->getEffectId();

	// �������� ��� ����� 
	strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

	// ��������� � ������ ������ ���
	this->tableContent[lastIndex].push_back(strValue);

	intValue = potion->getPower();
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// �������� ����
	intValue = potion->getPrice();
	// ��������� ���� 
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// �������� ���-��
	intValue = potion->getNumber();
	// ��������� ���-�� �����������
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// ������������� ������
	this->calculateData();
}

int PotionTablePrinter::findIndexInTableContentByKey(int key)
{
	int index = -1;

	int size = tableContent.size();

	string strKey = to_string(key);

	for (int i = 0; i < size; ++i)
	{
		// ���� ����� ���������
		if (strKey == tableContent[i][0])
		{
			index = i;

			break;
		}
	}

	return index;
}
