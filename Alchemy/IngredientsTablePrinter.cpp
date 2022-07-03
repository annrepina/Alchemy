#include "IngredientsTablePrinter.h"

IngredientsTablePrinter::IngredientsTablePrinter() : TablePrinter()
{
}

IngredientsTablePrinter::~IngredientsTablePrinter()
{
}

void IngredientsTablePrinter::update(int id)
{
	// если элементов меньше, чем id, значит был добавлен новый элемент
	if (this->tableContent.size() < id)
	{
		addIngredientToTableContent(id);
	}
	else
	{
		this->tableContent[id - 1].clear();

		changeTableContentForOneElement(id);
	}

}

#pragma region Методы расчета

int IngredientsTablePrinter::calculateNumberOfLines()
{
	// Кол-во строк равно кол-ву ингредиентов
	int numberOfLines = table->getEndIterator()->first;

	return numberOfLines;
}

int IngredientsTablePrinter::calculateWidth()
{
	int totalWidth = 0;

	for (auto width : this->columnWidthValues)
	{
		totalWidth += width;
	}

	totalWidth += NUMBER_OF_COLUMNS + 1;

	return totalWidth;
}

int IngredientsTablePrinter::calculateMaxId()
{
	// Последний id
	int maxId = (table->getEndIterator())->first;

	return maxId;
}

int IngredientsTablePrinter::calculateMaxIdStrSize()
{
	// Последний id
	int maxId = calculateMaxId();

	// Последний id в виде строки
	string strMaxId;

	// Размер строки последнего id 
	int maxStrIdSize;

	strMaxId = to_string(maxId);

	maxStrIdSize = strMaxId.size();

	return maxStrIdSize;
}

int IngredientsTablePrinter::calculateMaxNameSize()
{
	// Присваеваем самому длинному размеру размер имени первого ингредиента в map
	int maxNameSize = table->getStartIterator()->second->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// Присваиваем размер имени текущего элемента
		int size = i->second->getName().size();

		if (maxNameSize < size)
			maxNameSize = size;
	}

	return maxNameSize;
}

int IngredientsTablePrinter::calculateMaxNumberStrSize()
{
	// мах кол-во ингредиентов
	int maxNumber = table->getStartIterator()->second->getNumber();

	// мах кол-во ингредиентов в виде строки
	string strMaxNumber;

	// Размер строки мах кол-ва ингредиентов 
	int strMaxNumberSize;

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// Присваиваем кол-во текущего элемента
		int number = i->second->getNumber();

		if (maxNumber < number)
			maxNumber = number;
	}

	strMaxNumber = to_string(maxNumber);

	strMaxNumberSize = strMaxNumber.size();

	return strMaxNumberSize;
}

int IngredientsTablePrinter::calculateMaxEffectNameSize()
{
	// Итератор на map 
	map<int, bool>::iterator firstIter = table->getStartIterator()->second->getIteratorOfEffectsId();

	// Id-ключ первого элемента map
	int firstEffectId = firstIter->first;

	int maxEffectNameSize = table->getEffectsTable()->getEffectByKey(firstEffectId)->getName().size();

	map<int, Ingredient*>::iterator startIter = table->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++table->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// Для каждого ингредиента получаю свой итератор на map из эффектов, указывающий на 1ый элемент
		map<int, bool>::iterator effectIter = i->second->getIteratorOfEffectsId();

		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, ++effectIter)
		{
			// Id эффекта текущего ингредиента по соотв итератору
			int id = effectIter->first;

			// Расчитываем длину имени эффекта с текущим id 
			int effectNameSize = table->getEffectsTable()->getEffectByKey(id)->getName().size();

			if (maxEffectNameSize < effectNameSize)
				maxEffectNameSize = effectNameSize;
		}
	}

	return maxEffectNameSize;
}

vector<int> IngredientsTablePrinter::calculateColumnWidth()
{
	// Значения ширин колонки
	vector <int> columnWidth;

	// Считаем ширину столбца с id
	int idColumnWidth = calculateMaxIdStrSize() + GAPS;

	// Добавляем ширину колонки с id
	columnWidth.push_back(idColumnWidth);

	// Считаем ширину столбца с именем
	int nameColumnWidth = calculateMaxNameSize() + GAPS;

	// Добавляем ширину столбца с именем
	columnWidth.push_back(nameColumnWidth);

	// Считаем ширину столбца с ценой
	int priceColumnWidth = PRICE_LENGTH + GAPS;

	columnWidth.push_back(priceColumnWidth);

	int effectColumnWidth = calculateMaxEffectNameSize() + GAPS;
	
	// Добавляем ширину в вектор столько раз, сколько эффектов
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		columnWidth.push_back(effectColumnWidth);
	}

	//int numberColumnWidth = calculateMaxNumberStrSize(table) + GAPS;

	int numberColumnWidth = NUMBER_LENGTH + GAPS;

	columnWidth.push_back(numberColumnWidth);

	return columnWidth;
}

#pragma endregion Методы расчета

void IngredientsTablePrinter::print(int page)
{
	TablePrinter::print(page);

	this->printHeader();

	//// если совсем пустая, то заполняем
	//if (this->tableContent.size() == 0)
	//{
	//	this->fillInTableContent();
	//}

	this->printContent(page);
}

void IngredientsTablePrinter::printHeader()
{
	string namesOfColumns[NUMBER_OF_COLUMNS] = { "№", "Имя", "Цена", "Эффект 1", "Эффект 2", "Кол-во" };

	this->yCoordForContentPrinting = Y_COORD_FOR_HEADER_PRINTING;

	for (int i = 0; i < this->numberOfColumns; ++i)
	{
		cout << goToXY(this->yCoordForContentPrinting, this->xCoordsForContentPrinting[i]);

		cout << namesOfColumns[i];
	}
}

void IngredientsTablePrinter::printContent(int page)
{
	int border = page * NUMBER_OF_CONTENT_LINES;

	// сбрасываем координату
	this->yCoordForContentPrinting = Y_COORD_FOR_CONTENT_PRINTING;

	//// Итератор на начало 
	//map<int, Ingredient*>::iterator iter = table->getStartIterator();

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

void IngredientsTablePrinter::fillInTableContent()
{
	// Итератор на начало map в таблице
	map<int, Ingredient*>::iterator iter = table->getStartIterator();

	// Целое значение
	int intValue;

	// Строковое значение
	string strValue;

	// id эффекта ингредиента
	int effectId;

	// Известен ли игроку эффект данного ингредиента
	bool isEffectKnown;

	for (int i = 0; i < this->numberOfLines; ++i)
	{
		// Создаем внутренний вектор
		vector <string> line;

		// Добавляем этот вектор во внешний
		this->tableContent.push_back(line);

		// добываем id
		intValue = iter->first;

		// Добавляем в первый вектор id
		this->tableContent[i].push_back(to_string(intValue));

		// добываем имя
		strValue = iter->second->getName();

		// Добавляем в первый вектор имя
		this->tableContent[i].push_back(strValue);

		// добываем цену
		intValue = iter->second->getPrice();

		// Добавляем цену 
		this->tableContent[i].push_back(to_string(intValue));

		// для каждого ингредиента
		for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
		{
			// Итератор на map с эффектами у ингредиента
			map<int, bool>::iterator effectIter = iter->second->getIteratorOfEffectsId();

			// Добываем булеву
			isEffectKnown = effectIter->second;

			// имя эффекта
			string effectName;

			// если имя игроку известно
			if (isEffectKnown)
			{
				// Присваиваем id
				effectId = effectIter->first;

				// Присваиваем имя
				effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
			}
			else
				effectName = UNKNOWN_EFFECT;

			// Добавляем имя эффекта 
			this->tableContent[i].push_back(effectName);

			++effectIter;
		}

		intValue = iter->second->getNumber();

		// Добавляем кол-во ингредиента
		this->tableContent[i].push_back(to_string(intValue));

		// увеличиваем итератор
		++iter;
	}
}

void IngredientsTablePrinter::changeTableContentForOneElement(int id)
{
	// Id для контента таблицы
	int tableContentId = id - 1;

	Ingredient* ingredient = table->getIngredientById(id);

	// Известен ли игроку эффект данного ингредиента
	bool isEffectKnown;

	// Целое значение
	int intValue;

	// id эффекта ингредиента
	int effectId;

	// Строковое значение
	string strValue;

	// Добавляем в вектор id
	this->tableContent[tableContentId].push_back(to_string(id));

	// Строковое значение
	strValue = ingredient->getName();

	// добавляем имя
	this->tableContent[tableContentId].push_back(strValue);

	intValue = ingredient->getPrice();

	this->tableContent[tableContentId].push_back(to_string(intValue));

	// для каждого ингредиента
	for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
	{
		// Итератор на map с эффектами у ингредиента
		map<int, bool>::iterator effectIter = ingredient->getIteratorOfEffectsId();

		// Добываем булеву
		isEffectKnown = effectIter->second;

		// имя эффекта
		string effectName;

		// если имя игроку известно
		if (isEffectKnown)
		{
			// Присваиваем id
			effectId = effectIter->first;

			// Присваиваем имя
			effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
		}
		else
			effectName = UNKNOWN_EFFECT;

		// Добавляем имя эффекта 
		this->tableContent[tableContentId].push_back(effectName);

		++effectIter;
	}

	intValue = ingredient->getNumber();

	this->tableContent[tableContentId].push_back(to_string(intValue));

	// пересчитываем данные
	this->calculateData();
}

void IngredientsTablePrinter::addIngredientToTableContent(int id)
{
	// Итератор на конец map в таблице
	map<int, Ingredient*>::iterator endIter = table->getEndIterator();

	// последний индекс в содержимом таблицы равен последнему id в таблице
	int lastId = endIter->first - 1;

	// Целое значение
	int intValue;

	// Строковое значение
	string strValue;

	// id эффекта ингредиента
	int effectId;

	// Известен ли игроку эффект данного ингредиента
	bool isEffectKnown;

	// Создаем внутренний вектор
	vector <string> line;

	// Добавляем этот вектор во внешний
	this->tableContent.push_back(line);

	// добываем id
	intValue = endIter->first;

	// Добавляем в первый вектор id
	tableContent[lastId].push_back(to_string(intValue));

	// добываем имя
	strValue = endIter->second->getName();

	// Добавляем в вектор имя
	this->tableContent[lastId].push_back(strValue);

	// добываем цену
	intValue = endIter->second->getPrice();

	// Добавляем цену 
	this->tableContent[lastId].push_back(to_string(intValue));

	// для каждого ингредиента
	for (int j = 0; j < NUMBER_OF_EFFECTS; ++j)
	{
		// Итератор на map с эффектами у ингредиента
		map<int, bool>::iterator effectIter = endIter->second->getIteratorOfEffectsId();

		// Добываем булеву
		isEffectKnown = effectIter->second;

		// имя эффекта
		string effectName;

		// если имя игроку известно
		if (isEffectKnown)
		{
			// Присваиваем id
			effectId = effectIter->first;

			// Присваиваем имя
			effectName = table->getEffectsTable()->getEffectByKey(effectId)->getName();
		}
		else
			effectName = UNKNOWN_EFFECT;

		// Добавляем имя эффекта 
		this->tableContent[lastId].push_back(effectName);

		++effectIter;
	}

	intValue = endIter->second->getNumber();

	// Добавляем кол-во ингредиента
	this->tableContent[lastId].push_back(to_string(intValue));

	// пересчитываем данные
	this->calculateData();
}
