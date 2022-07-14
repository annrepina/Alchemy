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
		intValue = startIter->first;

		// Добавляем в первый вектор id
		this->tableContent[counter].push_back(to_string(intValue));

		// id эффекта
		int effectId = startIter->second->getEffectId();

		// добываем имя зелья 
		strValue = this->table->getEffectsTable()->getEffectByKey(effectId)->getName();

		// Добавляем в первый вектор имя
		this->tableContent[counter].push_back(strValue);

		// добываем цену
		intValue = startIter->second->getPrice();

		// Добавляем цену 
		this->tableContent[counter].push_back(to_string(intValue));

		// добываем кол-во
		intValue = startIter->second->getNumber();

		// Добавляем кол-во ингредиента
		this->tableContent[counter].push_back(to_string(intValue));
	}
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
		// если кол-во зелья больше 0
		if (i->second->getNumber() > 0)
		{
			++numberOfLines;
		}
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
