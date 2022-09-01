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
    this->title = "������ � �������";
    this->goToTitle = "�������� � �������";
    this->numberOfStates = 1;
    this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
    this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
    this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->potionTablePrinter = alchemicalUserInterface->getPotionTablePrinter();
}

void WorkWithPotionTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithPotionTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setListOfInnerMenuItems();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	setContent();

	// ��������� �������� �������
	int page = FIRST_PAGE;

	printMenuTitle();

	string error;

	// ���� ���-�� ��������� ����� ������ ������, �� ����������� ������ �� ������
	if (this->contentAfterSortingAndSearch.size() < MINIMUM_NUMBER_OF_POTIONTS)
	{
		error = "� ��� ������ ��� �����.\n�������� ���-������.\.\nESC - �����";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(listOfInnerMenuItems);

		//// ���������� ���� ����� ������ �����/����������
		//this->alchemicalUserInterface->setExitFlag(false);

		// ���� ���� ������ ������ �����
		if (currentYCursorCoordState == MAIN_MENU_Y_COORD + INNER_MENU_ITEMS - 1)
		{
			// ���������� ����������
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

		// ������ �����
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::PotionTable);

		// ���� �������� ��������
		if (numberOfColumn != NON_DIGIT_COLUMN)
			this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());

		else
			// ���������
			this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumn, orderOfSorting);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
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
    // ���� ������ ������
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&WorkWithPotionTableMenuState::createReturnMenuState);
    }
}

ReturnMenuState* WorkWithPotionTableMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
