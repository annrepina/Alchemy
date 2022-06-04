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

int IngredientsTablePrinter::calculateWidth(IngredientsTable* ingredientsTable)
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	//// Длина наибольшего id
	//width = calculateMaxIdStrSize(ingredientsTable);

	//// Длина наибольшего имени ингредиента
	//totalWidth += calculateMaxNameSize(ingredientsTable);

	//// Длина наибольшей цены
	//totalWidth += to_string(MAX_PRICE).size();

	//// Длина наибольшего кол-ва
	//totalWidth += calculateMaxNumberStrSize(ingredientsTable);

	//// Длины наибольших эффектов
	//totalWidth += calculateMaxEffectNameSize(ingredientsTable) * NUMBER_OF_EFFECTS;

	//// Прибавляем границы и пробелы
	//totalWidth += NUMBER_OF_COLUMNS * MULTIPLIER + 1;

	return totalWidth;
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

vector<int> IngredientsTablePrinter::calculateColumnWidth(IngredientsTable* table)
{
	// Значения ширин колонки
	vector <int> columnWidth;

	// Считаем ширину столбца с id
	int idColumnWidth = calculateMaxIdStrSize(table) + GAPS;

	// Добавляем ширину колонки с id
	columnWidth.push_back(idColumnWidth);

	// Считаем ширину столбца с именем
	int nameColumnWidth = calculateMaxNameSize(table) + GAPS;

	// Добавляем ширину столбца с именем
	columnWidth.push_back(nameColumnWidth);

	// Считаем ширину столбца с ценой
	int priceColumnWidth = to_string(MAX_PRICE).size();

	columnWidth.push_back(priceColumnWidth);

	int effectColumnWidth = calculateMaxEffectNameSize(table) + GAPS;
	
	// Добавляем ширину в вектор столько раз, сколько эффектов
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		columnWidth.push_back(effectColumnWidth);
	}

	int numberColumnWidth = calculateMaxNumberStrSize(table);

	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

//void IngredientsTablePrinter::printHeader(IngredientsTable* table)
//{
//	// Координата для печати названия
//	int xCoord = calculateXCoordInMiddle(table->getTitle());
//
//	// Перейти по координатам и увеличить Y
//	goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	// Печатаем верхнюю границу таблицы
//	printTopTableFrame(1, this->tableWidth - OUTER_BORDERS);
//
//	cout << goToXY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//	cout << VERTICAL_LINE;
//
//	// Координаты для печати названия табл
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
//	// По кол-ву колонок
//	for (int i = 0; i < this->numberOfLines; ++i)
//	{
//		goToCoordAndIncreaseY(this->yCoordForPrinting, this->xCoordForPrinting);
//
//		printInnerTableFrame(this->columnWidthValues);
//	}
//}
