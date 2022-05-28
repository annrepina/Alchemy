#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "�����������";
	this->numberOfColumns = NUMBER_OF_COLUMNS;
	//this->numberOfLines = (--this->ingredientsWithId.end())->first + 1;
}

IngredientsTable::~IngredientsTable()
{
}

void IngredientsTable::addIngredient(Ingredient* ingredient)
{
	this->ingredientsWithId.emplace(++id, ingredient);
}

void IngredientsTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void IngredientsTable::print() const
{
	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);
 
	// �������� ����� �������
	printTopTableFrame(1, this->length - OUTER_BORDERS);
	printLowerTableFrame(1, this->length - OUTER_BORDERS);




	//for (auto ingredient : this->ingredientsWithId)
	//{
	//	cout << ingredient.first << ' ';
	//	ingredient.second->print();

	//	// �������� �������
	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	//	{
	//		this->effectsTable->getEffectByKey(ingredient.second->getEffectId(i))->print();
	//		cout << ' ';
	//	}

	//	cout << endl;
	//}
}

void IngredientsTable::clear()
{
	for (auto ingredient : ingredientsWithId)
	{
		if (nullptr != ingredient.second)
		{
			delete ingredient.second;
			ingredient.second = nullptr;
		}
	}
}

void IngredientsTable::calculateLength()
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

	this->length = length;
}

int IngredientsTable::calculateMaxIdStrSize()
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

	maxId = (--this->ingredientsWithId.end())->first;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTable::calculateMaxNameSize()
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

int IngredientsTable::calculateMaxNumberStrSize()
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

int IngredientsTable::calculateMaxEffectNameSize()
{
	// ������ ������ � ������ �����������
	int firstEffectId = this->ingredientsWithId.begin()->second->

	int maxEffectNameSize = this->effectsTable->getEffectByKey(firstEffectId)->getName().size();

	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		// ��� ������� �����������
		for (auto ingredient : this->ingredientsWithId)
		{
			// Id ������� �������� �����������
			int id = ingredient.second->getEffectIsKnown(i);

			// ����������� ����� ����� ������� � ������� id 
			int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}
