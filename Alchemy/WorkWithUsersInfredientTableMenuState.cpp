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
	this->title = "������ � ������������� ��������";
	this->goToTitle = "�������� � ������������� ��������";
	this->numberOfStates = 1;
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
}

void WorkWithUsersInfredientTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithUsersInfredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setFields();

	printMenuTitle();

	// ���� ���-�� ��������� ������������ ������ ������, �� ������� ������ �� ������
	if (this->contentAfterSortingAndResearch.size() < MINIMUM_NUMBER_OF_INGREDIENTS)
	{
		string error = "� ��� ������ ��� ������������.\n������ ���-������ � ��������\.\nESC - �����";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(listOfInnerMenuItems);
	printFilterItems(this->listOfColumnFilters);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	workWithTable();
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

	this->contentAfterSortingAndResearch = this->initialContent;
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