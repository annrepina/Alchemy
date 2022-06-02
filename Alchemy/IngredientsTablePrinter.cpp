#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

void IngredientsTablePrinter::print(IngredientsTable* ingredientsTable)
{
	calculateLength(ingredientsTable);

	calculateXCoordForPrinting();
	
	printTableHeader(ingredientsTable);



}

void IngredientsTablePrinter::calculateLength(IngredientsTable* ingredientsTable)
{
	int length;

	for(auto wid)







	// ����� ����������� id
	length = calculateMaxIdStrSize(ingredientsTable);

	// ����� ����������� ����� �����������
	length += calculateMaxNameSize(ingredientsTable);

	// ����� ���������� ����
	length += to_string(MAX_PRICE).size();

	// ����� ����������� ���-��
	length += calculateMaxNumberStrSize(ingredientsTable);

	// ����� ���������� ��������
	length += calculateMaxEffectNameSize(ingredientsTable) * NUMBER_OF_EFFECTS;

	// ���������� ������� � �������
	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	this->tableLength = length;
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
	firstIter = table->getStartIterator()->second->getIterator();

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
		map<int, bool>::iterator iter = ingredient.second->getIterator();

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
	int priceColumnWidth = to_string(MAX_PRICE).size();

	columnWidth.push_back(priceColumnWidth);

	int effectColumnWidth = calculateMaxEffectNameSize(table) + GAPS;
	
	// ��������� ������ � ������ ������� ���, ������� ��������
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		columnWidth.push_back(effectColumnWidth);
	}

	int numberColumnWidth = calculateMaxNumberStrSize(table);

	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

void IngredientsTablePrinter::printTableHeader(IngredientsTable* table)
{
	// ���������� ��� ������ ��������
	int xCoord = calculateXCoordInMiddle(table->getTitle());

	// ������� �� ����������� � ��������� Y
	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

	// �������� ������� ������� �������
	printTopTableFrame(1, this->tableLength - OUTER_BORDERS);

	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);

	cout << VERTICAL_LINE;

	// ���������� ��� ������ �������� ����
	cout << goToXY(this->yCoordForPrinting, xCoord);

	cout << table->getTitle();

	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting + this->tableLength - 1);

	cout << VERTICAL_LINE;

	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

	printLowerTableFrame(1, this->tableLength - OUTER_BORDERS);
}
