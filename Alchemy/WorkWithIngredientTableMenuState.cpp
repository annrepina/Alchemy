#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

//string WorkWithIngredientTableMenuState::listOfColumnTitles[NUMBER_OF_INGREDIENT_TABLE_COLUMNS] = { "№", "Имя", "Цена", "Эффект 1", "Эффект 2", "Кол-во" };

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState()
{
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
	this->longestColumnSize = 0;
	this->xCoordForFilterValue = 0;
}

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Работа с ингредиентами";
	this->goToTitle = "Работать с ингредиентами";
	this->numberOfStates = 1;
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->longestColumnSize = 0;
	this->xCoordForFilterValue = 0;
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithIngredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setListOfInnerMenuItems();
	setListOfColumnTitles();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);
	fillMap<string>(columnForFiltration, listOfColumnTitles, currentYCursorCoordState, NUMBER_OF_INGREDIENT_TABLE_COLUMNS);

	setContent();

	longestColumnSize = calculateLongestFIlteringItem();

	xCoordForFilterValue = X_COORD_FOR_FILTER_ITEMS + longestColumnSize + GAP_BETWEEN_FILTER_AND_VALUE;

	// начальная страница таблицы
	int page = FIRST_PAGE;

	printMenuTitle();

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(this->listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

		//// сбрасываем флаг после выбора поиск/сортировка
		//this->alchemicalUserInterface->setExitFlag(false);

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

		//this->workWithTable((OperationCode)operationCode);
	}
}

MenuState* WorkWithIngredientTableMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

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
	for (int i = 0; i < NUMBER_OF_INGREDIENT_TABLE_COLUMNS; ++i)
	{
		string emptyStr = "";
		this->searchingQueries.push_back(emptyStr);
	}
}

void WorkWithIngredientTableMenuState::setContent()
{
	this->initialContent = this->ingredientTablePrinter->getTableContent();

	this->contentAfterSortingAndSearch = this->initialContent;
}

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
	int xCoordForColon = xCoordForFilterValue - 1;

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

void WorkWithIngredientTableMenuState::setListOfColumnTitles()
{
	// если вектор пустой
	if (this->listOfColumnTitles.empty())
	{
		this->listOfColumnTitles.push_back("№ от");
		this->listOfColumnTitles.push_back("Имя");
		this->listOfColumnTitles.push_back("Цена");
		this->listOfColumnTitles.push_back("Эффект 1");
		this->listOfColumnTitles.push_back("Эффект 2");
		this->listOfColumnTitles.push_back("Кол - во");
	}
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
			filterData();
		}
		break;

		case OperationCode::Sorting:
		{
			sortData();
		}
		break;
	}
}

void WorkWithIngredientTableMenuState::sortData()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		// делаем выбор
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		// если критерий цифровой
		if (numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_6)
			this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());

		else
			// сортируем
			this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumn, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
}

void WorkWithIngredientTableMenuState::filterData()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		int numberOfColumnForFiltration = 0;

		// Запрос на фильтрацию
		string requestForFiltration = "";

		bool isString = true;

		this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		// Текущая координата Y сбрасываем ее
		currentYCursorCoordState = MAIN_MENU_Y_COORD;

		printFilterItems(this->listOfColumnTitles);

		// выбираем пункт меню фильтрации
		chooseMenuItem(this->listOfColumnTitles, X_COORD_FOR_FILTER_ITEMS);

		////// делаем выбор
		//this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		numberOfColumnForFiltration = calculateNumberOfColumnForFiltration();

		isString = isStringColumn(numberOfColumnForFiltration);

		cout << goToXY(currentYCursorCoordState, xCoordForFilterValue);

		requestForFiltration = this->alchemicalUserInterface->checkInput(requestForFiltration, isString, 0, MAX_INT, currentYCursorCoordState, this->xCoordForFilterValue);

		//// если критерий цифровой
		//if (numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_6)
		//	this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());

		//else
		//	// сортируем
		//	this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


		//// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		//if (this->alchemicalUserInterface->getExitFlag() == true)
		//{
		//	// сбрасываем флаг
		//	this->alchemicalUserInterface->setExitFlag(false);

		//	return;
		//}

		//this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumn, orderOfSorting);

		//// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		//if (this->alchemicalUserInterface->getExitFlag() == true)
		//{
		//	// сбрасываем флаг
		//	this->alchemicalUserInterface->setExitFlag(false);

		//	return;
		//}
	}
}

int WorkWithIngredientTableMenuState::calculateLongestFIlteringItem()
{
	string longest = "";

	int size = 0;

	for (auto line : this->listOfColumnTitles)
	{
		if (longest.size() < line.size())
			longest = line;
	}

	size = longest.size();

	return size;
}

bool WorkWithIngredientTableMenuState::isStringColumn(int numberOfColumn)
{
	if (numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_6 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_1)
		return false;

	else
		return true;
}

int WorkWithIngredientTableMenuState::calculateNumberOfColumnForFiltration()
{

	int numberOfColumn = currentYCursorCoordState - MAIN_MENU_Y_COORD + 1;

	return numberOfColumn;

}
