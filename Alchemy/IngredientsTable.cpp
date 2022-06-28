#include "IngredientsTable.h"
#include <iostream>
#include "EffectsTable.h"

int IngredientsTable::id = 0;

IngredientsTable::IngredientsTable()
{
	this->effectsTable = nullptr;
	this->title = "Ингредиенты";
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
//	// Перейти по координатам и увеличить Y
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
// 
//	// Печатаем шапку таблицы
//	printTopTableFrame(1, this->length - OUTER_BORDERS);
//
//	// Координата для печати
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
//	//	// печатаем эффекты
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
	// размер вектор
	int size = this->observerList.size();

	// итератор на первый элемент в векторе
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
//	// Длина наибольшего id
//	length = calculateMaxIdStrSize();
//
//	// Длина наибольшего имени ингредиента
//	length += calculateMaxNameSize();
//
//	// Длина наибольшей цены
//	length += to_string(MAX_PRICE).size();
//
//	// Длина наибольшего кол-ва
//	length += calculateMaxNumberStrSize();
//
//	// Длины наибольших эффектов
//	length += calculateMaxEffectNameSize() * NUMBER_OF_EFFECTS;
//
//	// Прибавляем границы и пробелы
//	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;
//
//	this->length = length;
//}
//
//int IngredientsTable::calculateMaxIdStrSize()
//{
//	// Последний id
//	int maxId;
//
//	// Последний id в виде строки
//	string strMaxId;
//
//	// Размер строки последнего id 
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
//	// Присваеваем самому длинному размеру размер имени первого ингредиента в map
//	int maxNameSize = this->ingredientsWithId.begin()->second->getName().size();
//
//	// Для каждого ингредиента
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// Присваиваем размер имени текущего элемента
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
//	// мах кол-во ингредиентов
//	int maxNumberSize = this->ingredientsWithId.begin()->second->getNumber();
//
//	// мах кол-во ингредиентов в виде строки
//	string strMaxNumber;
//
//	// Размер строки мах кол-ва ингредиентов 
//	int strMaxNumberSize;
//
//	// Для каждого ингредиента
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// Присваиваем кол-вj текущего элемента
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
//	// Итератор на map 
//	map<int, bool>::iterator firstIter;
//
//	// Id-ключ первого элемента map
//	int firstEffectId;
//
//	// Итератор на первый эффект в первом ингредиенте
//	firstIter = this->ingredientsWithId.begin()->second->getIterator();
//
//	// Присваиваем id
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
//	//	// Для каждого ингредиента получаю свой итератор, указывающий на 1ый элемент
//	//	map<int, bool>::iterator iter = ingredient.second->getIterator();
//
//	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
//	//	{
//	//		// Id эффекта текущего ингредиента по соотв итератору
//	//		int id = iter->first;
//
//	//		// Расчитываем длину имени эффекта с текущим id 
//	//		int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();
//
//	//		if (maxEffectNameSize < effectNameSize)
//	//			maxEffectNameSize = effectNameSize;
//	//	}
//	//}
//
//	// Для каждого ингредиента
//	for (auto ingredient : this->ingredientsWithId)
//	{
//		// Для каждого ингредиента получаю свой итератор, указывающий на 1ый элемент
//		map<int, bool>::iterator iter = ingredient.second->getIterator();
//
//		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
//		{
//			// Id эффекта текущего ингредиента по соотв итератору
//			int id = iter->first;
//
//			// Расчитываем длину имени эффекта с текущим id 
//			int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();
//
//			if (maxEffectNameSize < effectNameSize)
//				maxEffectNameSize = effectNameSize;
//		}
//	}
//
//	return maxEffectNameSize;
//}
