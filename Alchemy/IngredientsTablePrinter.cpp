#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

//void IngredientsTablePrinter::print(IngredientsTable* table)
//{
//	this->columnWidthValues = calculateColumnWidth(table);
//
//	this->tableWidth = calculateWidth(table);
//
//	this->xCoordForPrinting = calculateXCoordForPrinting();
//	
//	printHeader(table);
//
//	printInnerFrame(table);
//}

int IngredientsTablePrinter::calculateNumberOfLines(IngredientsTable* table)
{
	// ���-�� ����� ����� ���-�� ������������
	int numberOfLines = table->getIngredientsWithId().size();

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

	//// ����� ����������� id
	//width = calculateMaxIdStrSize(ingredientsTable);

	//// ����� ����������� ����� �����������
	//totalWidth += calculateMaxNameSize(ingredientsTable);

	//// ����� ���������� ����
	//totalWidth += to_string(MAX_PRICE).size();

	//// ����� ����������� ���-��
	//totalWidth += calculateMaxNumberStrSize(ingredientsTable);

	//// ����� ���������� ��������
	//totalWidth += calculateMaxEffectNameSize(ingredientsTable) * NUMBER_OF_EFFECTS;

	//// ���������� ������� � �������
	//totalWidth += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	return totalWidth;
}

int IngredientsTablePrinter::calculateMaxIdStrSize(IngredientsTable* ingredientsTable)
{
	// ��������� id
	int maxId;

	// ��������� id � ���� ������
	string strMaxId;

	// ������ ������ ���������� id 
	int maxStrIdSize;

	//map<int, Ingredient*>::reverse_iterator rit;

	//rit = this->ingredientsWithId.rbegin();

	//biggest = rit->first;

	//ingredientsTable->getEndIterator()


	maxId = (--ingredientsTable->getEndIterator())->first;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTablePrinter::calculateMaxNameSize(IngredientsTable* table)
{
	// ����������� ������ �������� ������� ������ ����� ������� ����������� � map
	int maxNameSize = table->getStartIterator()->second->getName().size();

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// ��� ������� �����������
	for (auto ingredient : ingredientsWithId)
	{
		// ����������� ������ ����� �������� ��������
		int size = ingredient.second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize(IngredientsTable* table)
{
	// ��� ���-�� ������������
	int maxNumberSize = table->getStartIterator()->second->getNumber();

	// ��� ���-�� ������������ � ���� ������
	string strMaxNumber;

	// ������ ������ ��� ���-�� ������������ 
	int strMaxNumberSize;

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// ��� ������� �����������
	for (auto ingredient : ingredientsWithId)
	{
		// ����������� ���-�j �������� ��������
		int number = ingredient.second->getNumber();

		if (maxNumberSize < number)
			maxNumberSize = number;
	}

	strMaxNumber = to_string(maxNumberSize);

	strMaxNumberSize = strMaxNumber.size();

	return strMaxNumberSize;
}

int IngredientsTablePrinter::calculateMaxEffectNameSize(IngredientsTable* table)
{
	// �������� �� map 
	map<int, bool>::iterator firstIter;

	// Id-���� ������� �������� map
	int firstEffectId;

	// �������� �� ������ ������ � ������ �����������
	firstIter = table->getStartIterator()->second->getIteratorOfEffectsId();

	// ����������� id
	firstEffectId = firstIter->first;

	int maxEffectNameSize = table->getEffectsTable()->getEffectByKey(firstEffectId)->getName().size();



	//int size = this->ingredientsWithId.size();

	//for (int i = 0; i < size; ++i)
	//{
	//	// ��� ������� ����������� ������� ���� ��������, ����������� �� 1�� �������
	//	map<int, bool>::iterator iter = ingredient.second->getIterator();

	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
	//	{
	//		// Id ������� �������� ����������� �� ����� ���������
	//		int id = iter->first;

	//		// ����������� ����� ����� ������� � ������� id 
	//		int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();

	//		if (maxEffectNameSize < effectNameSize)
	//			maxEffectNameSize = effectNameSize;
	//	}
	//}

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// ��� ������� �����������
	for (auto ingredient : ingredientsWithId)
	{
		// ��� ������� ����������� ������� ���� ��������, ����������� �� 1�� �������
		map<int, bool>::iterator iter = ingredient.second->getIteratorOfEffectsId();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
		{
			// Id ������� �������� ����������� �� ����� ���������
			int id = iter->first;

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

void IngredientsTablePrinter::print(IngredientsTable* table)
{
	TablePrinter::print(table);

	this->printHeader();
}

void IngredientsTablePrinter::printHeader()
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "Id", "���", "����", "������ 1", "������ 2", "���-��" };

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

	// �������� �� ������ 
	map<int, Ingredient*>::iterator iter = table->getStartIterator();

	for (int i = 0; i < this->numberOfLines && i < border; ++i)
	{
		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << table->getStartIterator();


	}
}

void IngredientsTablePrinter::fillInTableContent(IngredientsTable* table)
{
	// �������� �� ������ map � �������
	map<int, Ingredient*>::iterator iter = table->getStartIterator();

	// ����� ��������
	int intValue;

	// ��������� ��������
	string strValue;

	// �������� �� map 
	map<int, bool>::iterator firstIter;

	// �������� map
	//map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	for (int i = 0; i < this->numberOfLines; ++i)
	{
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

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
		{

		}
		// ����������� ��������
		++iter;

	}
}

//void IngredientsTablePrinter::printHeader(IngredientsTable* table)
//{
//	// ���������� ��� ������ ��������
//	int xCoord = calculateXCoordInMiddle(table->getTitle());
//
//	// ������� �� ����������� � ��������� Y
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	// �������� ������� ������� �������
//	printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);
//
//	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	cout << VERTICAL_LINE;
//
//	// ���������� ��� ������ �������� ����
//	cout << goToXY(this->yCoordForPrinting, xCoord);
//
//	cout << table->getTitle();
//
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting + this->tableWidth - 1);
//
//	cout << VERTICAL_LINE;
//
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//
//
//	printLowerTableFrame(1, this->tableWidth - OUTER_BORDERS);
//}

//void IngredientsTablePrinter::printInnerFrame(IngredientsTable* table)
//{
//	// �� ���-�� �������
//	for (int i = 0; i < this->numberOfLines; ++i)
//	{
//		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//		printInnerTableFrame(this->columnWidthValues);
//	}
//}
