#include "WorkWithPotionTableMenuState.h"
//#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState()
{
    this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
    this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
    this->ingredientTablePrinter = nullptr;
	this->potionTablePrinter = nullptr;
}

WorkWithPotionTableMenuState::WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : WorkWithIngredientTableMenuState(alchemicalUserInterface)
{
    this->title = "Работа с зельями";
    this->goToTitle = "Работать с зельями";
    this->numberOfStates = 1;
    this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
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

	setListOfInnerMenuItems();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	setContent();

	// начальная страница таблицы
	int page = FIRST_PAGE;

	printMenuTitle();

	string error;

	// если кол-во доступных зелий меньше ОДНОГО, то сортировать ничего не выйдет
	if (this->contentAfterSortingAndSearch.size() < MINIMUM_NUMBER_OF_POTIONTS)
	{
		error = "У вас совсем нет зелий.\nСоздайте что-нибудь.\.\nESC - назад";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(listOfInnerMenuItems);

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

		workWithTable((OperationCode)operationCode);
	}
}

void WorkWithPotionTableMenuState::setContent()
{
	this->initialContent = this->potionTablePrinter->getTableContent();

	this->contentAfterSortingAndSearch = this->initialContent;
}

void WorkWithPotionTableMenuState::sortData()
{
	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		this->potionTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		//this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		// делаем выбор
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::PotionTable);

		// если критерий цифровой
		if (numberOfColumn != NON_DIGIT_COLUMN)
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

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumn, orderOfSorting);

		// если был выход из меню сортировки, то не покидаем совсем программу, а выходим только из сортировки
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// сбрасываем флаг
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
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
