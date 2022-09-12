#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState()
{
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
	this->longestFilterSize = 0;
	this->xCoordForFilterValue = 0;
}

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Работа с ингредиентами";
	this->goToTitle = "Работать с ингредиентами";
	this->numberOfStates = 1;
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->longestFilterSize = 0;
	this->xCoordForFilterValue = 0;
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithIngredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setFields();

	printMenuTitle();

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);
	printFilterItems(this->listOfColumnFilters);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	workWithTable();
}

MenuState* WorkWithIngredientTableMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void WorkWithIngredientTableMenuState::addSearchingQuery(string query, int numberOfQuery)
{
	int index = numberOfQuery - 1;

	// делаем проверку, были ли запросы до этого в этом фильтре
	// если они были
	if (searchingQueries[index] != "")
	{
		// то сбрасываем контент после сортировки и фильтрации до контента
		this->contentAfterSortingAndResearch = initialContent;

		// сортирум заново
		sortData();
	}

	// заменяем запрос
	searchingQueries[index] = query;
}

#pragma region Сеттеры

void WorkWithIngredientTableMenuState::setListOfStates()
{
	this->listOfCreatingFunctions.push_back(&WorkWithIngredientTableMenuState::createReturnMenuState);
}

void WorkWithIngredientTableMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&WorkWithIngredientTableMenuState::createReturnMenuState);
	}
}

void WorkWithIngredientTableMenuState::setSearchingQueriesDefault()
{
	for (int i = 0; i < NUMBER_OF_SEARCHING_QUERIES; ++i)
	{
		string emptyStr = "";
		this->searchingQueries.push_back(emptyStr);
	}
}

void WorkWithIngredientTableMenuState::setContent()
{
	this->initialContent = this->ingredientTablePrinter->getTableContent();

	this->contentAfterSortingAndResearch = this->initialContent;
}

void WorkWithIngredientTableMenuState::setListOfInnerMenuItems()
{
	// если вектор пустой
	if (this->listOfInnerMenuItems.empty())
	{
		this->listOfInnerMenuItems.push_back("Сортировка");
		this->listOfInnerMenuItems.push_back("Поиск");
		this->listOfInnerMenuItems.push_back("Назад");
	}
}

void WorkWithIngredientTableMenuState::setListOfColumnFilters()
{
	// если вектор пустой
	if (this->listOfColumnFilters.empty())
	{
		this->listOfColumnFilters.push_back("№ от");
		this->listOfColumnFilters.push_back("№ до");
		this->listOfColumnFilters.push_back("Имя");
		this->listOfColumnFilters.push_back("Цена от");
		this->listOfColumnFilters.push_back("Цена до");
		this->listOfColumnFilters.push_back("Эффект 1");
		this->listOfColumnFilters.push_back("Эффект 2");
		this->listOfColumnFilters.push_back("Кол - во от");
		this->listOfColumnFilters.push_back("Кол - во до");
	}
}

void WorkWithIngredientTableMenuState::setFields()
{
	setListOfInnerMenuItems();
	setListOfColumnFilters();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);
	fillMap<string>(columnForFiltration, listOfColumnFilters, currentYCursorCoordState, NUMBER_OF_SEARCHING_QUERIES);

	setContent();
	setSearchingQueriesDefault();

	longestFilterSize = calculateLongestFIlteringItem();

	xCoordForFilterValue = X_COORD_FOR_FILTER_ITEMS + longestFilterSize + GAP_BETWEEN_FILTER_AND_VALUE;

	// начальная страница таблицы
	int page = FIRST_PAGE;
}

#pragma endregion Сеттеры

ReturnMenuState* WorkWithIngredientTableMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void WorkWithIngredientTableMenuState::printMenuItems(vector<string> listOfItems)
{
	int border = this->boundaryYCoord + listOfItems.size() - MAIN_MENU_Y_COORD;

	int index = this->currentYCursorCoordState - MAIN_MENU_Y_COORD;

	// Печатаем ассоциативный массив
	for (int i = index; i < border; ++i)
	{
		if (i == index)
		{
			printTextWithBackground(listOfItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// Печатаем пункт меню
			cout << listOfItems[i] << endl;
	}
}

void WorkWithIngredientTableMenuState::printFilterItems(vector<string> listOfItems)
{
	int border = this->boundaryYCoord + listOfItems.size()- MAIN_MENU_Y_COORD;

	int index = this->currentYCursorCoordState - MAIN_MENU_Y_COORD;

	// Координата x для печати двоеточия
	int xCoordForColon = xCoordForFilterValue - COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE;

	// Печатаем ассоциативный массив
	for (int i = index, j = this->currentYCursorCoordState; i < border; ++i, ++j)
	{
		cout << goToXY(j, X_COORD_FOR_FILTER_ITEMS);

		if (i == index)
		{
			printTextWithBackground(listOfItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

			cout << goToXY(j, xCoordForColon) << ':';\
		}

		else
			// Печатаем пункт меню
			cout << listOfItems[i] << goToXY(j, xCoordForColon) << ':';
	}

	// Возвращаемся в координаты
	cout << goToXY(currentYCursorCoordState, X_COORD_FOR_FILTER_ITEMS);
}

void WorkWithIngredientTableMenuState::workWithTable()
{
	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(this->listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

		// если была нажата кнопка назад
		if (currentYCursorCoordState == MAIN_MENU_Y_COORD + INNER_MENU_ITEMS - 1)
		{
			// сбрасываем координату
			this->currentYCursorCoordState = MAIN_MENU_Y_COORD;

			this->alchemicalUserInterface->setState(this->getNextState());

			return;
		}

		int operationCode = defineOperation();

		this->workWithTable((OperationCode)operationCode);
	}
}

void WorkWithIngredientTableMenuState::checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items)
{
		// если граничная координата не равна текущей
	if (borderYCoord != this->currentYCursorCoordState)
	{
		// Если кнопка вниз
		if (VK_DOWN == keyCode)
		{
			cout << goToXY(currentYCursorCoordState, xCoordForItemPrinting);

			// Печатаем пункт меню без выделения
			cout << items[currentYCursorCoordState - MAIN_MENU_Y_COORD];

			// увеличиваем координаты
			++this->currentYCursorCoordState;
		}
		// если кнопка вверх
		else
			// уменьшаем координаты
			--this->currentYCursorCoordState;

		// Переходим по координатам
		cout << goToXY(this->currentYCursorCoordState, xCoordForItemPrinting);

		if(xCoordForItemPrinting > STANDARD_CURSOR_X_COORD)
			printFilterItems(items);

		else
			printMenuItems(items);

		// Возвращаемся в координаты
		cout << goToXY(currentYCursorCoordState, xCoordForItemPrinting);
	}
}

void WorkWithIngredientTableMenuState::chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting)
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	// Флаг для выхода из цикла, но не выход из программы
	bool innerExitFlag = false;

	do
	{
		// Проверяем нажатую кнопку
		this->alchemicalUserInterface->checkMenuChoice();

		switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
		{
			case VK_UP:
			{
				this->checkVerticalArrowsChoice(this->boundaryYCoord, xCoordForItemsPrinting, VK_UP, listOfItems);
			}
			break;

			case VK_DOWN:
			{
				// Проверяем стрелочки
				this->checkVerticalArrowsChoice(this->boundaryYCoord + listOfItems.size() - 1, xCoordForItemsPrinting, VK_DOWN, listOfItems);
			}
			break;

			case VK_RETURN:
			{
				// выход из цикла
				innerExitFlag = true;
			}
			break;

			case VK_ESCAPE:
			{
				this->alchemicalUserInterface->setExitFlag(true);
				//exitFlag = true;
			}
			break;
		}
	} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
}

int WorkWithIngredientTableMenuState::defineOperation()
{
	int operationCode = currentYCursorCoordState - MAIN_MENU_Y_COORD;

	return operationCode;
}

void WorkWithIngredientTableMenuState::workWithTable(OperationCode operationCode)
{
	switch (operationCode)
	{
		case OperationCode::Search:
		{
			launchFilterMenu();
		}
		break;

		case OperationCode::Sorting:
		{
			launchSortingMenu();
		}
		break;
	}
}

void WorkWithIngredientTableMenuState::launchSortingMenu()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		this->ingredientTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// делаем выбор
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumnforSorting, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		// если таблица не пустая
		if(contentAfterSortingAndResearch.size() > 0) 
			sortData();

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumnforSorting, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
}

void WorkWithIngredientTableMenuState::sortData()
{
	// если критерий цифровой
	if (numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_6)
		this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());

	else
		// сортируем
		this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
}

void WorkWithIngredientTableMenuState::launchFilterMenu()
{
	// Текущая координата Y сбрасываем ее
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	printFilterItems(this->listOfColumnFilters);

	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		int numberOfSearchingQuery = 0;

		// Запрос на фильтрацию
		string queryForFiltration = "";

		bool isString = true;

		this->ingredientTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// выбираем пункт меню фильтрации
		chooseMenuItem(this->listOfColumnFilters, X_COORD_FOR_FILTER_ITEMS);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			currentYCursorCoordState = MAIN_MENU_Y_COORD + 1;

			return;
		}

		numberOfSearchingQuery = calculateNumberOfColumnForFiltration();

		isString = isStringColumn(numberOfSearchingQuery);

		cout << goToXY(currentYCursorCoordState, xCoordForFilterValue) << eraseOnLine(FROM_CURSOR_TO_SCREEN_END);

		queryForFiltration = this->alchemicalUserInterface->checkInput(queryForFiltration, isString, 0, MAX_INT, currentYCursorCoordState, this->xCoordForFilterValue);

		addSearchingQuery(queryForFiltration, numberOfSearchingQuery);

		filterData();

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumnforSorting, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			currentYCursorCoordState = MAIN_MENU_Y_COORD + 1;

			return;
		}
	}
}

void WorkWithIngredientTableMenuState::filterData()
{
	int size = contentAfterSortingAndResearch.size();

	int numberOfColumns = this->ingredientTablePrinter->getNumberOfColumns();

	// буферный контент
	vector<vector<string>> bufferContent;

	for (int i = 0; i < size; ++i)
	{
		// индекс фильтруемого столбца
		int index = 0;

		// индекс запроса в векторе запросов
		int indexOfQuery = 0;

		bool success = false;

		for (int j = 0; j < numberOfColumns; ++j)
		{
			bool isInt = false;
			int intValue = 0;

			if(indexOfQuery != (FILTER_NAME_3 - 1) && indexOfQuery != (FILTER_EFFECT_6 - 1) && indexOfQuery != (FILTER_EFFECT_7 - 1) || searchingQueries[indexOfQuery] != "")
				isInt = tryParseToInt(searchingQueries[indexOfQuery]);

			// если текущий запрос это число
			if (isInt == true)
			{
				int min = 0;

				intValue = stoi(contentAfterSortingAndResearch[i][j]);

				// если первый запрос не пустой
				if (this->searchingQueries[indexOfQuery] != "")
				{
					min = stoi(this->searchingQueries[indexOfQuery]);
				}

				++indexOfQuery;

				int max = MAX_INT;

				// если второй запрос не пустой
				if (this->searchingQueries[indexOfQuery] != "")
				{
					max = stoi(this->searchingQueries[indexOfQuery]);
				}

				++indexOfQuery;

				// если число не попадает в диапазон, то выходим из цикла
				if (min > intValue || intValue > max)
				{
					success = false;
					break;
				}

				success = true;
			}

			else
			{
				// если запросы не совпадают
				if (this->searchingQueries[indexOfQuery] != "" && !hasSubstring(contentAfterSortingAndResearch[i][j], this->searchingQueries[indexOfQuery]))
				{
					success = false;
					break;
				}

				++indexOfQuery;

				success = true;
			}
		}

		if (success)
			bufferContent.push_back(contentAfterSortingAndResearch[i]);
	}

	contentAfterSortingAndResearch = bufferContent;
}

int WorkWithIngredientTableMenuState::calculateLongestFIlteringItem()
{
	string longest = "";

	int size = 0;

	for (auto line : this->listOfColumnFilters)
	{
		if (longest.size() < line.size())
			longest = line;
	}

	size = longest.size();

	return size;
}

bool WorkWithIngredientTableMenuState::isStringColumn(int numberOfColumn)
{
	return numberOfColumn == FILTER_NAME_3 || numberOfColumn == FILTER_EFFECT_6 || numberOfColumn == FILTER_EFFECT_7;
}

int WorkWithIngredientTableMenuState::calculateNumberOfColumnForFiltration()
{
	int numberOfColumn = currentYCursorCoordState - MAIN_MENU_Y_COORD + 1;

	return numberOfColumn;
}