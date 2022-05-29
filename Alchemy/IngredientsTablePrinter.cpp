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

	// Длина наибольшего id
	length = calculateMaxIdStrSize();

	// Длина наибольшего имени ингредиента
	length += calculateMaxNameSize();

	// Длина наибольшей цены
	length += to_string(MAX_PRICE).size();

	// Длина наибольшего кол-ва
	length += calculateMaxNumberStrSize();

	// Длины наибольших эффектов
	length += calculateMaxEffectNameSize() * NUMBER_OF_EFFECTS;

	// Прибавляем границы и пробелы
	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	this->tableLength = length;
}

int IngredientsTablePrinter::calculateMaxIdStrSize(Table* table)
{
	// Последний id
	int maxId;

	// Последний id в виде строки
	string strMaxId;

	// Размер строки последнего id 
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
	// Присваеваем самому длинному размеру размер имени первого ингредиента в map
	int maxNameSize = this->ingredientsWithId.begin()->second->getName().size();

	// Для каждого ингредиента
	for (auto ingredient : this->ingredientsWithId)
	{
		// Присваиваем размер имени текущего элемента
		int size = ingredient.second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize()
{
	// мах кол-во ингредиентов
	int maxNumberSize = this->ingredientsWithId.begin()->second->getNumber();

	// мах кол-во ингредиентов в виде строки
	string strMaxNumber;

	// Размер строки мах кол-ва ингредиентов 
	int strMaxNumberSize;

	// Для каждого ингредиента
	for (auto ingredient : this->ingredientsWithId)
	{
		// Присваиваем кол-вj текущего элемента
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
	// Итератор на map 
	map<int, bool>::iterator firstIter;

	// Id-ключ первого элемента map
	int firstEffectId;

	// Итератор на первый эффект в первом ингредиенте
	firstIter = this->ingredientsWithId.begin()->second->getIterator();

	// Присваиваем id
	firstEffectId = firstIter->first;

	int maxEffectNameSize = this->effectsTable->getEffectByKey(firstEffectId)->getName().size();



	//int size = this->ingredientsWithId.size();

	//for (int i = 0; i < size; ++i)
	//{
	//	// Для каждого ингредиента получаю свой итератор, указывающий на 1ый элемент
	//	map<int, bool>::iterator iter = ingredient.second->getIterator();

	//	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
	//	{
	//		// Id эффекта текущего ингредиента по соотв итератору
	//		int id = iter->first;

	//		// Расчитываем длину имени эффекта с текущим id 
	//		int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();

	//		if (maxEffectNameSize < effectNameSize)
	//			maxEffectNameSize = effectNameSize;
	//	}
	//}

	// Для каждого ингредиента
	for (auto ingredient : this->ingredientsWithId)
	{
		// Для каждого ингредиента получаю свой итератор, указывающий на 1ый элемент
		map<int, bool>::iterator iter = ingredient.second->getIterator();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
		{
			// Id эффекта текущего ингредиента по соотв итератору
			int id = iter->first;

			// Расчитываем длину имени эффекта с текущим id 
			int effectNameSize = this->effectsTable->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}
