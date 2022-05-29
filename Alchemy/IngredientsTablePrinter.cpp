#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

void IngredientsTablePrinter::print(IngredientsTable* ingredientsTable)
{
	calculateLength(ingredientsTable);

	calculateXCoordForPrinting();

	// Перейти по координатам и увеличить Y
	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

	// Печатаем шапку таблицы
	printTopTableFrame(1, this->tableLength - OUTER_BORDERS);

	// Координата для печати
	int xCoord = calculateXCoordInMiddle(ingredientsTable->getTitle());

	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);

	cout << VERTICAL_LINE;

	cout << goToXY(this->yCoordForPrinting, xCoord);

	cout << ingredientsTable->getTitle();

	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting + this->tableLength - 1);

	//cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting + length - 1);

	cout << VERTICAL_LINE;

	//cout << goToXY(this->yCoordForPrinting + 1, this->xCoordForPrinting);

	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);

	printLowerTableFrame(1, this->tableLength - OUTER_BORDERS);
}

void IngredientsTablePrinter::calculateLength(IngredientsTable* ingredientsTable)
{
	int length;

	// Длина наибольшего id
	length = calculateMaxIdStrSize(ingredientsTable);

	// Длина наибольшего имени ингредиента
	length += calculateMaxNameSize(ingredientsTable);

	// Длина наибольшей цены
	length += to_string(MAX_PRICE).size();

	// Длина наибольшего кол-ва
	length += calculateMaxNumberStrSize(ingredientsTable);

	// Длины наибольших эффектов
	length += calculateMaxEffectNameSize(ingredientsTable) * NUMBER_OF_EFFECTS;

	// Прибавляем границы и пробелы
	length += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	this->tableLength = length;
}

int IngredientsTablePrinter::calculateMaxIdStrSize(IngredientsTable* ingredientsTable)
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

	//ingredientsTable->getEndIterator()


	maxId = (--ingredientsTable->getEndIterator())->first;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTablePrinter::calculateMaxNameSize(IngredientsTable* table)
{
	// Присваеваем самому длинному размеру размер имени первого ингредиента в map
	int maxNameSize = table->getStartIterator()->second->getName().size();

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// Для каждого ингредиента
	for (auto ingredient : ingredientsWithId)
	{
		// Присваиваем размер имени текущего элемента
		int size = ingredient.second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize(IngredientsTable* table)
{
	// мах кол-во ингредиентов
	int maxNumberSize = table->getStartIterator()->second->getNumber();

	// мах кол-во ингредиентов в виде строки
	string strMaxNumber;

	// Размер строки мах кол-ва ингредиентов 
	int strMaxNumberSize;

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// Для каждого ингредиента
	for (auto ingredient : ingredientsWithId)
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

int IngredientsTablePrinter::calculateMaxEffectNameSize(IngredientsTable* table)
{
	// Итератор на map 
	map<int, bool>::iterator firstIter;

	// Id-ключ первого элемента map
	int firstEffectId;

	// Итератор на первый эффект в первом ингредиенте
	firstIter = table->getStartIterator()->second->getIterator();

	// Присваиваем id
	firstEffectId = firstIter->first;

	int maxEffectNameSize = table->getEffectsTable()->getEffectByKey(firstEffectId)->getName().size();



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

	map<int, Ingredient*> ingredientsWithId = table->getIngredientsWithId();

	// Для каждого ингредиента
	for (auto ingredient : ingredientsWithId)
	{
		// Для каждого ингредиента получаю свой итератор, указывающий на 1ый элемент
		map<int, bool>::iterator iter = ingredient.second->getIterator();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++iter)
		{
			// Id эффекта текущего ингредиента по соотв итератору
			int id = iter->first;

			// Расчитываем длину имени эффекта с текущим id 
			int effectNameSize = table->getEffectsTable()->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}
