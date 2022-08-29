#include "PotionTablePrinter.h"

PotionTablePrinter::PotionTablePrinter()
{
}

PotionTablePrinter::~PotionTablePrinter()
{
}

void PotionTablePrinter::print(int page)
{
	TablePrinter::print(page);

	this->printHeader();

	this->printContent(page);
}

void PotionTablePrinter::print(vector<vector<string>> content, int page, int numberOfColumn, bool orderOfSorting)
{
}

void PotionTablePrinter::printWithSortingMarkers(int page, int numberOfColumn, bool orderOfSorting)
{
	TablePrinter::print(page);

	this->printHeader(numberOfColumn, orderOfSorting);

	this->printContent(page);
}

void PotionTablePrinter::fillInTableContent()
{
	// Итератор на начало map в таблице
	auto startIter = table->getStartIterator();

	// итератор на конец map
	auto endIter = table->getEndIterator();

	// Целое значение
	int intValue;

	// Строковое значение
	string strValue;

	// Счетчик
	int counter = 0;

	for (auto i = startIter; i != endIter; ++i, ++counter)
	{
		// Создаем внутренний вектор
		vector <string> line;

		// Добавляем этот вектор во внешний
		this->tableContent.push_back(line);

		// добываем id
		intValue = i->first;

		// Добавляем в первый вектор id
		this->tableContent[counter].push_back(to_string(intValue));

		// id эффекта
		int effectId = i->second->getEffectId();

		// добываем имя зелья 
		strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

		// Добавляем в первый вектор имя
		this->tableContent[counter].push_back(strValue);

		intValue = i->second->getPower();

		this->tableContent[counter].push_back(to_string(intValue));

		// добываем цену
		intValue = i->second->getPrice();

		// Добавляем цену 
		this->tableContent[counter].push_back(to_string(intValue));

		// добываем кол-во
		intValue = i->second->getNumber();

		// Добавляем кол-во ингредиента
		this->tableContent[counter].push_back(to_string(intValue));
	}
}

void PotionTablePrinter::printAvailableElements(int page)
{
}

void PotionTablePrinter::update()
{
	calculateData();
}

#pragma region Методы расчета

int PotionTablePrinter::calculateNumberOfLines()
{
	// итератор на начало map
	auto startIter = table->getStartIterator();

	// итератор на конец map
	auto endIter = table->getEndIterator();

	// кол-во строк
	int numberOfLines = 0;

	for (auto i = startIter; i != endIter; ++i)
	{
		//// если кол-во зелья больше 0
		//if (i->second->getNumber() > 0)
		//{
			++numberOfLines;
		//}
	}


	return numberOfLines;
}

vector<int> PotionTablePrinter::calculateColumnWidth()
{
	// Значения ширин колонки
	vector <int> columnWidth;

	// Считаем ширину столбца с номером зелья
	int idColumnWidth = calculateMaxId() + GAPS;

	// Добавляем ширину колонки с id
	columnWidth.push_back(idColumnWidth);

	// Считаем ширину столбца с именем
	int nameColumnWidth = calculateMaxNameSize() + GAPS;

	// Добавляем ширину столбца с именем
	columnWidth.push_back(nameColumnWidth);

	int powerColumnWidth = calculateMaxPowerStrSize() + GAPS;

	// Добавляем ширину столбца мощности
	columnWidth.push_back(powerColumnWidth);

	// Считаем ширину столбца с ценой
	int priceColumnWidth = calculateMaxPriceStrSize() + GAPS;

	columnWidth.push_back(priceColumnWidth);

	int numberColumnWidth = calculateMaxNumberStrSize() + GAPS;

	// добавляем ширину столбца с кол-вом
	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

int PotionTablePrinter::calculateWidth()
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	return totalWidth;
}

int PotionTablePrinter::calculateMaxId()
{
	int maxIdSize = to_string(calculateNumberOfLines()).size();

	return maxIdSize;
}

int PotionTablePrinter::calculateMaxNameSize()
{
	auto startIter = this->table->getEffectsTable()->getStartIterator();

	auto endIter = this->table->getEffectsTable()->getEndIterator();

	// Присваеваем самому длинному размеру размер имени первого эффекта в map
	int maxNameSize = startIter->second->getName().size();

	for (auto i = startIter; i != endIter; ++i)
	{
		// Присваиваем размер имени текущего элемента
		int size = i->second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int PotionTablePrinter::calculateMaxNumberStrSize()
{
	auto startIter = table->getStartIterator();

	auto endIter = table->getEndIterator();

	if (startIter != endIter)
	{
		// мах кол-во зелья
		int maxNumber = startIter->second->getNumber();

		for (auto i = startIter; i != endIter; ++i)
		{
			// Присваиваем кол-во текущего элемента
			int number = i->second->getNumber();

			if (maxNumber < number)
				maxNumber = number;
		}

		maxNumber = to_string(maxNumber).size();

		if (maxNumber > NUMBER_LENGTH)
			return maxNumber;

		else
			return NUMBER_LENGTH;
	}

	return 0;
}

int PotionTablePrinter::calculateMaxPowerStrSize()
{
	auto startIter = this->table->getStartIterator();
	auto endIter = this->table->getEndIterator();

	if (startIter != endIter)
	{
		int maxPower = startIter->second->getPower();

		for (auto i = startIter; i != endIter; ++i)
		{
			int power = i->second->getPower();

			if (maxPower < power)
				maxPower = power;
		}

		maxPower = to_string(maxPower).size();

		if (maxPower > POWER_LENGTH)
			return maxPower;

		else
			return POWER_LENGTH;
	}

	return 0;
}

int PotionTablePrinter::calculateMaxPriceStrSize()
{
	auto startIter = this->table->getStartIterator();
	auto endIter = this->table->getEndIterator();

	if (startIter != endIter)
	{
		int maxPrice = startIter->second->getPrice();

		for (auto i = startIter; i != endIter; ++i)
		{
			int price = i->second->getPrice();

			if (maxPrice < price)
				maxPrice = price;
		}

		maxPrice = to_string(maxPrice).size();

		if (maxPrice > PRICE_LENGTH)
			return maxPrice;

		else
			return PRICE_LENGTH;
	}

	return 0;
}

#pragma endregion Методы расчета

void PotionTablePrinter::printHeader()
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "№", "Имя", "Мощность", "Цена", "Кол-во"};

	this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	for (int i = 0; i < this->numberOfColumns; ++i)
	{
		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << namesOfColumns[i];
	}
}

void PotionTablePrinter::printHeader(int numberOfColumn, bool ordreOfSorting)
{
	//string namesOfColumns[NUMBER_OF_COLUMNS] = { "№", "Имя", "Мощность", "Цена", "Кол-во" };

	//this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	//// уменьшаем на 1, т.к. нумерация с нуля
	//numberOfColumn -= 1;

	//for (int i = 0; i < this->numberOfColumns; ++i)
	//{
	//	//int xCoord = 0;

	//	if (i == numberOfColumn)
	//	{
	//		if(ordreOfSorting == ASC)
	//		printColoredTextByCoords()

	//		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i] - 1);
	//	}

	//	cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i] - 1);

	//	

	//	printColoredTextByCoords("^")

	//	cout << namesOfColumns[i];
	//}
}

void PotionTablePrinter::printContent(int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// сбрасываем координату
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

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

void PotionTablePrinter::printContent(vector<vector<string>> content, int page)
{
}

void PotionTablePrinter::printAvailableContent(int page)
{
}

void PotionTablePrinter::changeTableContentForOneElement(int id)
{
	int index = -1;

	string strIndex = to_string(id);

	int tableContentSize = this->tableContent.size();

	index = findIndexInTableContentByKey(id);

	// очищаем данный элемент
	this->tableContent[index].clear();

	Potion* potion = table->getPotionById(id);

	if (potion->getNumber() == 0)
	{
		// итератор на начало и конец вектора с контентом
		auto beginIter = this->tableContent.begin();
		auto endIter = this->tableContent.begin();

		// итератор на начало вектора с доступными пользователю id
		auto beginIterOfAvailableContent = this->availableElementsId.begin();

		int startIndex = 0;

		// перебираем в цикле вектор
		for (auto i = beginIter; i != endIter; ++i, ++startIndex, ++beginIterOfAvailableContent)
		{
			// если сравнялись индексы
			if (startIndex == index)
			{
				// то присваиваем текущий итератор
				beginIter = i;
				break;
			}
		}

		// удаляем данный элемент из вектора контента и доступных id
		this->tableContent.erase(beginIter);
		this->availableElementsId.erase(beginIterOfAvailableContent);

		// пересчитываем данные
		this->calculateData();

		return;
	}

	// Целое значение
	int intValue;

	// Строковое значение
	string strValue;

	// Добавляем в первый вектор id
	this->tableContent[index].push_back(to_string(id));

	// id эффекта
	int effectId = potion->getEffectId();

	// добываем имя зелья 
	strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

	// Добавляем в первый вектор имя
	this->tableContent[index].push_back(strValue);

	intValue = potion->getPower();

	this->tableContent[index].push_back(to_string(intValue));

	// добываем цену
	intValue = potion->getPrice();

	// Добавляем цену 
	this->tableContent[index].push_back(to_string(intValue));

	// добываем кол-во
	intValue = potion->getNumber();

	// Добавляем кол-во ингредиента
	this->tableContent[index].push_back(to_string(intValue));

	// пересчитываем данные
	this->calculateData();
}

void PotionTablePrinter::changeTableContentForOneElement(int id, int previousNumber)
{
}

void PotionTablePrinter::addElementToTableContent(int id)
{
	this->availableElementsId.push_back(id);

	Potion* potion = table->getPotionById(id);

	//// последний индекс в содержимом таблицы 
	//int lastIndex = findIndexInTableContentByKey(id);

	int lastIndex = tableContent.size();

	// Целое значение
	int intValue;

	// Строковое значение
	string strValue;

	// id эффекта ингредиента
	int effectId;

	// Создаем внутренний вектор
	vector <string> line;

	// Добавляем этот вектор во внешний
	this->tableContent.push_back(line);

	//// добываем id
	//intValue = endIter->first;

	// Добавляем в первый вектор id
	tableContent[lastIndex].push_back(to_string(id));

	// id эффекта
	effectId = potion->getEffectId();

	// добываем имя зелья 
	strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

	// Добавляем в первый вектор имя
	this->tableContent[lastIndex].push_back(strValue);

	intValue = potion->getPower();
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// добываем цену
	intValue = potion->getPrice();
	// Добавляем цену 
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// добываем кол-во
	intValue = potion->getNumber();
	// Добавляем кол-во ингредиента
	this->tableContent[lastIndex].push_back(to_string(intValue));

	// пересчитываем данные
	this->calculateData();
}

int PotionTablePrinter::findIndexInTableContentByKey(int key)
{
	int index = -1;

	int size = tableContent.size();

	string strKey = to_string(key);

	for (int i = 0; i < size; ++i)
	{
		// если ключи совпадают
		if (strKey == tableContent[i][0])
		{
			index = i;

			break;
		}
	}

	return index;
}
