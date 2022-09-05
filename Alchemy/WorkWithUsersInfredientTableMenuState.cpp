#include "WorkWithUsersInfredientTableMenuState.h"
#include "AlchemicalUserInterface.h"

WorkWithUsersInfredientTableMenuState::WorkWithUsersInfredientTableMenuState()
{
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
}

WorkWithUsersInfredientTableMenuState::WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : WorkWithIngredientTableMenuState(alchemicalUserInterface)
{
	this->title = "������ � ������������� ��������";
	this->goToTitle = "�������� � ������������� ��������";
	this->numberOfStates = 1;
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
}

void WorkWithUsersInfredientTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithUsersInfredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setListOfInnerMenuItems();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	setContent();

	// ��������� �������� �������
	int page = FIRST_PAGE;

	printMenuTitle();

	string error;

	// ���� ���-�� ��������� ������������ ������ ������, �� ������� ������ �� ������
	if (this->contentAfterSortingAndSearch.size() < MINIMUM_NUMBER_OF_INGREDIENTS)
	{
		error = "� ��� ������ ��� ������������.\n������ ���-������ � ��������\.\nESC - �����";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(listOfInnerMenuItems);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

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

void WorkWithUsersInfredientTableMenuState::setContent()
{
	// �������� ������ � ���������
	auto content = this->ingredientTablePrinter->getTableContent();

	// �.�. ��������� ������� � ����
	int index = NUMBER_OF_COLUMN_WITH_NUMBER_OF_INGREDIENTS - 1;

	for (auto line : content)
	{
		if (stoi(line[index]) > 0)
			this->initialContent.push_back(line);
	}

	this->contentAfterSortingAndSearch = this->initialContent;
}

void WorkWithUsersInfredientTableMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
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
