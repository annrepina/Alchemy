#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

//string WorkWithIngredientTableMenuState::listOfColumnTitles[NUMBER_OF_INGREDIENT_TABLE_COLUMNS] = { "�", "���", "����", "������ 1", "������ 2", "���-��" };

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
	this->title = "������ � �������������";
	this->goToTitle = "�������� � �������������";
	this->numberOfStates = 1;
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->longestColumnSize = 0;
	this->xCoordForFilterValue = 0;
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
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

	// ��������� �������� �������
	int page = FIRST_PAGE;

	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(this->listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

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
	// ���� ������ ������
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

	// �������� ������������� ������
	for (int i = index; i < border; ++i)
	{
		if (i == index)
		{
			printTextWithBackground(listOfItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// �������� ����� ����
			cout << listOfItems[i] << endl;
	}
}

void WorkWithIngredientTableMenuState::printFilterItems(vector<string> listOfItems)
{
	int border = this->boundaryYCoord + listOfItems.size()- MAIN_MENU_Y_COORD;

	int index = this->currentYCursorCoordState - MAIN_MENU_Y_COORD;

	// ���������� x ��� ������ ���������
	int xCoordForColon = xCoordForFilterValue - 1;

	// �������� ������������� ������
	for (int i = index, j = this->currentYCursorCoordState; i < border; ++i, ++j)
	{
		cout << goToXY(j, X_COORD_FOR_FILTER_ITEMS);

		if (i == index)
		{
			printTextWithBackground(listOfItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

			cout << goToXY(j, xCoordForColon) << ':';\
		}

		else
			// �������� ����� ����
			cout << listOfItems[i] << goToXY(j, xCoordForColon) << ':';
	}

	// ������������ � ����������
	cout << goToXY(currentYCursorCoordState, X_COORD_FOR_FILTER_ITEMS);
}

void WorkWithIngredientTableMenuState::checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items)
{
		// ���� ��������� ���������� �� ����� �������
	if (borderYCoord != this->currentYCursorCoordState)
	{
		// ���� ������ ����
		if (VK_DOWN == keyCode)
		{
			cout << goToXY(currentYCursorCoordState, xCoordForItemPrinting);

			// �������� ����� ���� ��� ���������
			cout << items[currentYCursorCoordState - MAIN_MENU_Y_COORD];

			// ����������� ����������
			++this->currentYCursorCoordState;
		}
		// ���� ������ �����
		else
			// ��������� ����������
			--this->currentYCursorCoordState;

		// ��������� �� �����������
		cout << goToXY(this->currentYCursorCoordState, xCoordForItemPrinting);

		if(xCoordForItemPrinting > STANDARD_CURSOR_X_COORD)
			printFilterItems(items);

		else
			printMenuItems(items);

		// ������������ � ����������
		cout << goToXY(currentYCursorCoordState, xCoordForItemPrinting);
	}
}

void WorkWithIngredientTableMenuState::chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting)
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	// ���� ��� ������ �� �����, �� �� ����� �� ���������
	bool innerExitFlag = false;

	do
	{
		// ��������� ������� ������
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
				// ��������� ���������
				this->checkVerticalArrowsChoice(this->boundaryYCoord + listOfItems.size() - 1, xCoordForItemsPrinting, VK_DOWN, listOfItems);
			}
			break;

			case VK_RETURN:
			{
				// ����� �� �����
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
	// ���� ������ ������
	if (this->listOfInnerMenuItems.empty())
	{
		this->listOfInnerMenuItems.push_back("����������");
		this->listOfInnerMenuItems.push_back("�����");
		this->listOfInnerMenuItems.push_back("�����");
	}
}

void WorkWithIngredientTableMenuState::setListOfColumnTitles()
{
	// ���� ������ ������
	if (this->listOfColumnTitles.empty())
	{
		this->listOfColumnTitles.push_back("� ��");
		this->listOfColumnTitles.push_back("���");
		this->listOfColumnTitles.push_back("����");
		this->listOfColumnTitles.push_back("������ 1");
		this->listOfColumnTitles.push_back("������ 2");
		this->listOfColumnTitles.push_back("��� - ��");
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

		// ������ �����
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		// ���� �������� ��������
		if (numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_6)
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

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumn, orderOfSorting);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
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

		// ������ �� ����������
		string requestForFiltration = "";

		bool isString = true;

		this->ingredientTablePrinter->print(contentAfterSortingAndSearch, page, numberOfColumn, orderOfSorting);

		// ������� ���������� Y ���������� ��
		currentYCursorCoordState = MAIN_MENU_Y_COORD;

		printFilterItems(this->listOfColumnTitles);

		// �������� ����� ���� ����������
		chooseMenuItem(this->listOfColumnTitles, X_COORD_FOR_FILTER_ITEMS);

		////// ������ �����
		//this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumn, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		numberOfColumnForFiltration = calculateNumberOfColumnForFiltration();

		isString = isStringColumn(numberOfColumnForFiltration);

		cout << goToXY(currentYCursorCoordState, xCoordForFilterValue);

		requestForFiltration = this->alchemicalUserInterface->checkInput(requestForFiltration, isString, 0, MAX_INT, currentYCursorCoordState, this->xCoordForFilterValue);

		//// ���� �������� ��������
		//if (numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumn == INGREDIENT_TABLE_DIGIT_COLUMN_6)
		//	this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());

		//else
		//	// ���������
		//	this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndSearch[0], numberOfColumn, orderOfSorting, contentAfterSortingAndSearch.size());


		//// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		//if (this->alchemicalUserInterface->getExitFlag() == true)
		//{
		//	// ���������� ����
		//	this->alchemicalUserInterface->setExitFlag(false);

		//	return;
		//}

		//this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndSearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumn, orderOfSorting);

		//// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		//if (this->alchemicalUserInterface->getExitFlag() == true)
		//{
		//	// ���������� ����
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
