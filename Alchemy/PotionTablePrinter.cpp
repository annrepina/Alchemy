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
		intValue = startIter->first;

		// ��������� � ������ ������ id
		this->tableContent[counter].push_back(to_string(intValue));

		// id �������
		int effectId = startIter->second->getEffectId();

		// �������� ��� ����� 
		strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

		// ��������� � ������ ������ ���
		this->tableContent[counter].push_back(strValue);

		// �������� ����
		intValue = startIter->second->getPrice();

		// ��������� ���� 
		this->tableContent[counter].push_back(to_string(intValue));

		// �������� ���-��
		intValue = startIter->second->getNumber();

		// ��������� ���-�� �����������
		this->tableContent[counter].push_back(to_string(intValue));
	}
}

void PotionTablePrinter::printAvailableElements(int page)
{
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

void PotionTablePrinter::printAvailableContent(int page)
{
}

void PotionTablePrinter::changeTableContentForOneElement(int id)
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
		intValue = startIter->first;

		// ��������� � ������ ������ id
		this->tableContent[counter].push_back(to_string(intValue));

		// id �������
		int effectId = startIter->second->getEffectId();

		// �������� ��� ����� 
		strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

		// ��������� � ������ ������ ���
		this->tableContent[counter].push_back(strValue);

		// �������� ����
		intValue = startIter->second->getPrice();

		// ��������� ���� 
		this->tableContent[counter].push_back(to_string(intValue));

		// �������� ���-��
		intValue = startIter->second->getNumber();

		// ��������� ���-�� �����������
		this->tableContent[counter].push_back(to_string(intValue));
	}





	//// !!!����� ����������� ����� �� �������� 

	int index = -1;

	string strIndex = to_string(id);

	int tableContentSize = this->tableContent.size();

	for (int i = 0; i < tableContentSize; ++i)
	{
		// ���� ����� ���������
		if (strIndex == tableContent[i][0])
		{
			index = i;

			break;
		}
	}




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

	//// ���� ����� ������������ ����� 1, �� ����������� ���-�� ��������� ���������
	//if (intValue == 1)
	//	++numberOfAvailableContent;

	//// ���� ����� 0, �� ���������
	//else if (intValue == 0)
	//	--numberOfAvailableContent;

	// ������������� ������
	this->calculateData();
}

void PotionTablePrinter::changeTableContentForOneElement(int id, int previousNumber)
{

}

void PotionTablePrinter::addElementToTableContent(int id)
{

}
