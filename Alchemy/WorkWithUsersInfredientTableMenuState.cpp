#include "WorkWithUsersInfredientTableMenuState.h"
#include "AlchemicalUserInterface.h"

WorkWithUsersInfredientTableMenuState::WorkWithUsersInfredientTableMenuState()
{
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
}

WorkWithUsersInfredientTableMenuState::WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : WorkWithIngredientTableMenuState(alchemicalUserInterface)
{
	this->title = "Работа с ингредиентами алхимика";
	this->goToTitle = "Работать с ингредиентами алхимика";
	this->numberOfStates = 1;
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
}

void WorkWithUsersInfredientTableMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithUsersInfredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	//setListOfInnerMenuItems();
	//setListOfColumnTitles();

	//fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);
	//fillMap<string>(columnForFiltration, listOfColumnForFiltration, currentYCursorCoordState, NUMBER_OF_SEARCHING_QUERIES);

	//setContent();
	//setSearchingQueriesDefault();

	//longestColumnSize = calculateLongestFIlteringItem();

	//xCoordForFilterValue = X_COORD_FOR_FILTER_ITEMS + longestColumnSize + GAP_BETWEEN_FILTER_AND_VALUE;

	//// начальная страница таблицы
	//int page = FIRST_PAGE;

	setFields();

	printMenuTitle();

	// если кол-во доступных ингредиентов меньше ОДНОГО, то продать ничего не выйдет
	if (this->contentAfterSortingAndResearch.size() < MINIMUM_NUMBER_OF_INGREDIENTS)
	{
		string error = "У вас совсем нет ингредиентов.\nКупите что-нибудь у Аркадиии\.\nESC - назад";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(listOfInnerMenuItems);

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

void WorkWithUsersInfredientTableMenuState::setContent()
{
	// получаем вектор с контентом
	auto content = this->ingredientTablePrinter->getTableContent();

	// т.к. нумерация вектора с нуля
	int index = NUMBER_OF_COLUMN_WITH_NUMBER_OF_INGREDIENTS - 1;

	for (auto line : content)
	{
		if (stoi(line[index]) > 0)
			this->initialContent.push_back(line);
	}

	this->contentAfterSortingAndResearch = this->initialContent;
}

void WorkWithUsersInfredientTableMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&WorkWithUsersInfredientTableMenuState::createReturnMenuState);
	}
}

ReturnMenuState* WorkWithUsersInfredientTableMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

MenuState* WorkWithUsersInfredientTableMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}
