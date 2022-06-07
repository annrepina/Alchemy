#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

int IngredientsTablePrinter::calculateNumberOfLines(IngredientsTable* table)
{
	// ���-�� ����� ����� ���-�� ������������
	int numberOfLines = table->getEndIterator()->first;

	return numberOfLines;
}

int IngredientsTablePrinter::calculateWidth(IngredientsTable* ingredientsTable)
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	return totalWidth;
}

int IngredientsTablePrinter::calculateMaxId(IngredientsTable* table)
{
	// ��������� id
	int maxId = (table->getEndIterator())->first;

	return maxId;
}

int IngredientsTablePrinter::calculateMaxIdStrSize(IngredientsTable* ingredientsTable)
{
	// ��������� id
	int maxId = calculateMaxId(ingredientsTable);

	// ��������� id � ���� ������
	string strMaxId;

	// ������ ������ ���������� id 
	int maxStrIdSize;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTablePrinter::calculateMaxNameSize(IngredientsTable* table)
{
	// ����������� ������ �������� ������� ������ ����� ������� ����������� � map
	int maxNameSize = table->getStartIterator()->second->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ����������� ������ ����� �������� ��������
		int size = i->second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize(IngredientsTable* table)
{
	// ��� ���-�� ������������
	int maxNumber = table->getStartIterator()->second->getNumber();

	// ��� ���-�� ������������ � ���� ������
	string strMaxNumber;

	// ������ ������ ��� ���-�� ������������ 
	int strMaxNumberSize;

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ����������� ���-�j �������� ��������
		int number = i->second->getNumber();

		if (maxNumber < number)
			maxNumber = number;
	}

	strMaxNumber = to_string(maxNumber);

	strMaxNumberSize = strMaxNumber.size();

	return strMaxNumberSize;
}

int IngredientsTablePrinter::calculateMaxEffectNameSize(IngredientsTable* table)
{
	// �������� �� map 
	map<int, bool>::iterator firstIter = table->getStartIterator()->second->getIteratorOfEffectsId();

	// Id-���� ������� �������� map
	int firstEffectId = firstIter->first;

	int maxEffectNameSize = table->getEffectsTable()->getEffectByKey(firstEffectId)->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// ��� ������� ����������� ������� ���� �������� �� map �� ��������, ����������� �� 1�� �������
		map<int, bool>::iterator effectIter = i->second->getIteratorOfEffectsId();

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

vector<int> IngredientsTablePrinter::calculateColumnWidth(IngredientsTable* table)
{
	// �������� ����� �������
	vector <int> columnWidth;

	// ������� ������ ������� � id
	int idColumnWidth = calculateMaxIdStrSize(table) + GAPS;

	// ��������� ������ ������� � id
	columnWidth.push_back(idColumnWidth);

	// ������� ������ ������� � ������
	int nameColumnWidth = calculateMaxNameSize(table) + GAPS;

	// ��������� ������ ������� � ������
	columnWidth.push_back(nameColumnWidth);

	// ������� ������ ������� � �����
	int priceColumnWidth = PRICE_LENGTH + GAPS;

	columnWidth.push_back(priceColumnWidth);

	int effectColumnWidth = calculateMaxEffectNameSize(table) + GAPS;
	
	// ��������� ������ � ������ ������� ���, ������� ��������
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		columnWidth.push_back(effectColumnWidth);
	}

	//int numberColumnWidth = calculateMaxNumberStrSize(table) + GAPS;

	int numberColumnWidth = NUMBER_LENGTH + GAPS;

	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

void IngredientsTablePrinter::print(IngredientsTable* table, int page)
{
	TablePrinter::print(table, page);

	this->printHeader();

	this->fillInTableContent(table);

	this->printContent(table, page);
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

void IngredientsTablePrinter::printContent(IngredientsTable* table, int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// ���������� ����������
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

	//// �������� �� ������ 
	//map<int, Ingredient*>::iterator iter = table->getStartIterator();

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

void IngredientsTablePrinter::fillInTableContent(IngredientsTable* table)
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

		// ��� ������� �����������
		for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
		{
			// �������� �� map � ��������� � �����������
			map<int, bool>::iterator effectIter = iter->second->getIteratorOfEffectsId();

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
