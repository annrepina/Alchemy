#include "WorkWithPotionTableMenuState.h"
//#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState()
{
    this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
    this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
    this->ingredientTablePrinter = nullptr;
	this->potionTablePrinter = nullptr;
}

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : WorkWithIngredientTableMenuState(alchemicalUserInterface)
{
    this->title = "Работа с зельями";
    this->goToTitle = "Работать с зельями";
    this->numberOfStates = 1;
    this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
    this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
    this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->potionTablePrinter = alchemicalUserInterface->getPotionTablePrinter();
}

void WorkWithPotionTableMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithPotionTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setFields();

	//setListOfInnerMenuItems();

	//fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	//setContent();

	//// начальная страница таблицы
	//int page = FIRST_PAGE;

	printMenuTitle();

	// если кол-во доступных зелий меньше ОДНОГО, то сортировать ничего не выйдет
	if (this->contentAfterSortingAndResearch.size() < MINIMUM_NUMBER_OF_POTIONTS)
	{
		string error = "У вас совсем нет зелий.\nСоздайте что-нибудь.\.\nESC - назад";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	printFilterItems(this->listOfColumnForFiltration);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	//while (this->alchemicalUserInterface->getExitFlag() == false)
	//{
	//	chooseMenuItem(listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

	//	// если была нажата кнопка назад
	//	if (currentYCursorCoordState == MAIN_MENU_Y_COORD + INNER_MENU_ITEMS - 1)
	//	{
	//		// сбрасываем координату
	//		this->currentYCursorCoordState = MAIN_MENU_Y_COORD;

	//		this->alchemicalUserInterface->setState(this->getNextState());

	//		return;
	//	}

	//	int operationCode = defineOperation();

	//	workWithTable((OperationCode)operationCode);
	//}

	workWithTable();
}

void WorkWithPotionTableMenuState::setContent()
{
	this->initialContent = this->potionTablePrinter->getTableContent();

	this->contentAfterSortingAndResearch = this->initialContent;
}

//void WorkWithPotionTableMenuState::sortData()
//{
//	while (this->alchemicalUserInterface->getExitFlag() != true)
//	{
//		int page = FIRST_PAGE;
//
//		this->potionTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);
//
//		//this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);
//
//		// делаем выбор
//		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumnforSorting, orderOfSorting, AlchemicalUserInterface::TableCode::PotionTable);
//
//		// если критерий цифровой
//		if (numberOfColumnforSorting != NON_DIGIT_COLUMN)
//			this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
//
//		else
//			// сортируем
//			this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
//
//
//		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
//		if (this->alchemicalUserInterface->getExitFlag() == true)
//		{
//			// сбрасываем флаг
//			this->alchemicalUserInterface->setExitFlag(false);
//
//			return;
//		}
//
//		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumnforSorting, orderOfSorting);
//
//		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
//		if (this->alchemicalUserInterface->getExitFlag() == true)
//		{
//			// сбрасываем флаг
//			this->alchemicalUserInterface->setExitFlag(false);
//
//			return;
//		}
//	}
//}

void WorkWithPotionTableMenuState::setListOfColumnTitles()
{
	// если вектор пустой
	if (this->listOfColumnForFiltration.empty())
	{
		this->listOfColumnForFiltration.push_back("№ от");
		this->listOfColumnForFiltration.push_back("№ до");
		this->listOfColumnForFiltration.push_back("Имя");
		this->listOfColumnForFiltration.push_back("Мощность от");
		this->listOfColumnForFiltration.push_back("Мощность до");
		this->listOfColumnForFiltration.push_back("Цена от");
		this->listOfColumnForFiltration.push_back("Цена до");
		this->listOfColumnForFiltration.push_back("Кол - во от");
		this->listOfColumnForFiltration.push_back("Кол - во до");
	}
}

void WorkWithPotionTableMenuState::launchFilterMenu()
{
	// Текущая координата Y сбрасываем ее
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	printFilterItems(this->listOfColumnForFiltration);

	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		int numberOfSearchingQuery = 0;

		// Запрос на фильтрацию
		string queryForFiltration = "";

		bool isString = true;

		this->potionTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// выбираем пункт меню фильтрации
		chooseMenuItem(this->listOfColumnForFiltration, X_COORD_FOR_FILTER_ITEMS);

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

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumnforSorting, orderOfSorting);

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

void WorkWithPotionTableMenuState::launchSortingMenu()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		this->potionTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// делаем выбор
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumnforSorting, orderOfSorting, AlchemicalUserInterface::TableCode::PotionTable);

		sortData();

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumnforSorting, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
}

bool WorkWithPotionTableMenuState::isStringColumn(int numberOfColumn)
{
	return numberOfColumn == FILTER_NAME_3;
}

void WorkWithPotionTableMenuState::sortData()
{
	// если критерий цифровой
	if (numberOfColumnforSorting != NON_DIGIT_COLUMN)
		this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());

	else
		// сортируем
		this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
}

void WorkWithPotionTableMenuState::filterData()
{
	int size = contentAfterSortingAndResearch.size();

	int numberOfColumns = this->potionTablePrinter->getNumberOfColumns();

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

			if (indexOfQuery != (FILTER_NAME_3 - 1) || searchingQueries[indexOfQuery] != "")
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

MenuState* WorkWithPotionTableMenuState::getNextState()
{
    return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void WorkWithPotionTableMenuState::setListOfStates()
{
    this->listOfCreatingFunctions.push_back(&WorkWithPotionTableMenuState::createReturnMenuState);
}

void WorkWithPotionTableMenuState::setListOfCreatingFunctions()
{
    // если вектор пустой
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&WorkWithPotionTableMenuState::createReturnMenuState);
    }
}

ReturnMenuState* WorkWithPotionTableMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
