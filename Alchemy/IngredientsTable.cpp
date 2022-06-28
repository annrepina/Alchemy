#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "�����������";
	//this->numberOfColumns = NUMBER_OF_COLUMNS;
	//this->numberOfLines = (--this->ingredientsWithId.end())->first + 1;
}

IngredientsTable::~IngredientsTable()
{
	clear();
}

void IngredientsTable::add(Ingredient* ingredient)
{
	this->ingredientsWithId.emplace(++id, ingredient);
}

void IngredientsTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

//void IngredientsTable::print() 
//{
//	//cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	// ������� �� ����������� � ��������� Y
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
// 
//	// �������� ����� �������
//	printTopTableFrame(1, this->length - OUTER_BORDERS);
//
//	// ���������� ��� ������
//	int xCoord = calculateXCoordInMiddle(title);
//
//	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	cout << VERTICAL_LINE;
//
//	cout << goToXY(this->yCoordForPrinting, xCoord);
//
//	cout << title;
//
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting + length - 1);
//
//	//cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting + length - 1);
//
//	cout << VERTICAL_LINE;
//
//	//cout << goToXY(this->yCoordForPrinting + 1, this->xCoordForPrinting);
//
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	printLowerTableFrame(1, this->length - OUTER_BORDERS);
//
//
//
//
//	//for (auto ingredient : this->ingredientsWithId)
//	//{
//	//	cout << ingredient.first << ' ';
//	//	ingredient.second->print();
//
//	//	// �������� �������
//	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
//	//	{
//	//		this->effectsTable->getEffectByKey(ingredient.second->getEffectId(i))->print();
//	//		cout << ' ';
//	//	}
//
//	//	cout << endl;
//	//}
//}

map<int, Ingredient*>::iterator IngredientsTable::getEndIterator()
{
	return --this->ingredientsWithId.end();
}

map<int, Ingredient*>::iterator IngredientsTable::getStartIterator()
{
	return this->ingredientsWithId.begin();
}

//map<int, Ingredient*> IngredientsTable::getIngredientsWithId()
//{
//	return this->ingredientsWithId;
//}

EffectsTable* IngredientsTable::getEffectsTable()
{
	return this->effectsTable;
}

Ingredient* IngredientsTable::getIngredientById(int id)
{
	return this->ingredientsWithId[id];
}

void IngredientsTable::subscribe(IObserver* observer)
{
	this->observerList.push_back(observer);
}

void IngredientsTable::unsubscribe(IObserver* observer)
{
	// ������ ������
	int size = this->observerList.size();

	// �������� �� ������ ������� � �������
	auto begin = this->observerList.cbegin();	

	for (int i = 0; i < size; ++i)
	{
		if (this->observerList[i] == observer)
		{
			this->observerList.erase(begin + i);
			break;
		}
	}
}

void IngredientsTable::Notify(int id)
{
	for (auto observer : this->observerList)
	{
		observer->update(id);
	}
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

//void IngredientsTable::calculateLength()
//{
//	int length;
//
//	// ����� ����������� id
//	length = calculateMaxIdStrSize();
//
//	// ����� ����������� ����� �����������
//	length += calculateMaxNameSize();
//
//	// ����� ���������� ����
//	length += to_string(MAX_PRICE).size();
//
//	// ����� ����������� ���-��
//	length += calculateMaxNumberStrSize();
//
//	// ����� ���������� ��������
//	length += calculateMaxEffectNameSize() * NUMBER_OF_EFFECTS;
//
//	// ���������� ������� � �������
//	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;
//
//	this->length = length;
//}
//
//int IngredientsTable::calculateMaxIdStrSize()
//{
//	// ��������� id
//	int maxId;
//
//	// ��������� id � ���� ������
//	string strMaxId;
//
//	// ������ ������ ���������� id 
//	int maxStrIdSize;
//
//	//map<int, Ingredient*>::reverse_iterator rit;
//
//	//rit = this->ingredientsWithId.rbegin();
//
//	//biggest = rit->first;
//
//	maxId = (--this->ingredientsWithId.end())->first;
//
//	strMaxId = to_string(maxId);
//
//	maxStrIdSize = strMaxId.size();
//
//	return maxStrIdSize;
//}
//
//int IngredientsTable::calculateMaxNameSize()
//{
//	// ����������� ������ �������� ������� ������ ����� ������� ����������� � map
//	int maxNameSize = this->ingredientsWithId.begin()->second->getName().size();
//
//	// ��� ������� �����������
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// ����������� ������ ����� �������� ��������
//		int size = ingredient.second->getName().size();
//
//		if (maxNameSize < size)
//			maxNameSize = size;
//	}
//
//	return maxNameSize;
//}
//
//int IngredientsTable::calculateMaxNumberStrSize()
//{
//	// ��� ���-�� ������������
//	int maxNumberSize = this->ingredientsWithId.begin()->second->getNumber();
//
//	// ��� ���-�� ������������ � ���� ������
//	string strMaxNumber;
//
//	// ������ ������ ��� ���-�� ������������ 
//	int strMaxNumberSize;
//
//	// ��� ������� �����������
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// ����������� ���-�j �������� ��������
//		int number = ingredient.second->getNumber();
//
//		if (maxNumberSize < number)
//			maxNumberSize = number;
//	}
//
//	strMaxNumber = to_string(maxNumberSize);
//
//	strMaxNumberSize = strMaxNumber.size();
//
//	return strMaxNumberSize;
//}
//
//int IngredientsTable::calculateMaxEffectNameSize()
//{
//	// �������� �� map 
//	map<int, bool>::iterator firstIter;
//
//	// Id-���� ������� �������� map
//	int firstEffectId;
//
//	// �������� �� ������ ������ � ������ �����������
//	firstIter = this->ingredientsWithId.begin()->second->getIterator();
//
//	// ����������� id
//	firstEffectId = firstIter->first;
//
//	int maxEffectNameSize = this->effectsTable->getEffectByKey(firstEffectId)->getName().size();
//
//
//
//	//int size = this->ingredientsWithId.size();
//
//	//for (int i = 0; i < size; ++i)
//	//{
//	//	// ��� ������� ����������� ������� ���� ��������, ����������� �� 1�� �������
//	//	map<int, bool>::iterator iter = ingredient.second->getIterator();
//
//	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
//	//	{
//	//		// Id ������� �������� ����������� �� ����� ���������
//	//		int id = iter->first;
//
//	//		// ����������� ����� ����� ������� � ������� id 
//	//		int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();
//
//	//		if (maxEffectNameSize < effectNameSize)
//	//			maxEffectNameSize = effectNameSize;
//	//	}
//	//}
//
//	// ��� ������� �����������
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// ��� ������� ����������� ������� ���� ��������, ����������� �� 1�� �������
//		map<int, bool>::iterator iter = ingredient.second->getIterator();
//
//		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
//		{
//			// Id ������� �������� ����������� �� ����� ���������
//			int id = iter->first;
//
//			// ����������� ����� ����� ������� � ������� id 
//			int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();
//
//			if (maxEffectNameSize < effectNameSize)
//				maxEffectNameSize = effectNameSize;
//		}
//	}
//
//	return maxEffectNameSize;
//}
