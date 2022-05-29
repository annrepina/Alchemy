#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

void IngredientsTablePrinter::print(IngredientsTable* ingredientsTable)
{
	calculateLength(ingredientsTable);
}

void IngredientsTablePrinter::calculateLength(IngredientsTable* ingredientsTable)
{
	int length;

	// ����� ����������� id
	length = calculateMaxIdStrSize();

	// ����� ����������� ����� �����������
	length += calculateMaxNameSize();

	// ����� ���������� ����
	length += to_string(MAX_PRICE).size();

	// ����� ����������� ���-��
	length += calculateMaxNumberStrSize();

	// ����� ���������� ��������
	length += calculateMaxEffectNameSize() * NUMBER_OF_EFFECTS;

	// ���������� ������� � �������
	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	this->tableLength = length;
}

int IngredientsTablePrinter::calculateMaxIdStrSize(Table* table)
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

	maxId = (table.getEndIterator())

	maxId = (--this->ingredientsWithId.end())->first;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTablePrinter::calculateMaxNameSize()
{
	// ����������� ������ �������� ������� ������ ����� ������� ����������� � map
	int maxNameSize = this->ingredientsWithId.begin()->second->getName().size();

	// ��� ������� �����������
	for (auto ingredient : this->ingredientsWithId)
	{
		// ����������� ������ ����� �������� ��������
		int size = ingredient.second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize()
{
	// ��� ���-�� ������������
	int maxNumberSize = this->ingredientsWithId.begin()->second->getNumber();

	// ��� ���-�� ������������ � ���� ������
	string strMaxNumber;

	// ������ ������ ��� ���-�� ������������ 
	int strMaxNumberSize;

	// ��� ������� �����������
	for (auto ingredient : this->ingredientsWithId)
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

int IngredientsTablePrinter::calculateMaxEffectNameSize()
{
	// �������� �� map 
	map<int, bool>::iterator firstIter;

	// Id-���� ������� �������� map
	int firstEffectId;

	// �������� �� ������ ������ � ������ �����������
	firstIter = this->ingredientsWithId.begin()->second->getIterator();

	// ����������� id
	firstEffectId = firstIter->first;

	int maxEffectNameSize = this->effectsTable->getEffectByKey(firstEffectId)->getName().size();



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

	// ��� ������� �����������
	for (auto ingredient : this->ingredientsWithId)
	{
		// ��� ������� ����������� ������� ���� ��������, ����������� �� 1�� �������
		map<int, bool>::iterator iter = ingredient.second->getIterator();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
		{
			// Id ������� �������� ����������� �� ����� ���������
			int id = iter->first;

			// ����������� ����� ����� ������� � ������� id 
			int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}
