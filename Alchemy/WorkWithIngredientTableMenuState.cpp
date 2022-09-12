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
	this->title = "������ � �������������";
	this->goToTitle = "�������� � �������������";
	this->numberOfStates = 1;
	this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
	this->longestFilterSize = 0;
	this->xCoordForFilterValue = 0;
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithIngredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setFields();

	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
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

	// ������ ��������, ���� �� ������� �� ����� � ���� �������
	// ���� ��� ����
	if (searchingQueries[index] != "")
	{
		// �� ���������� ������� ����� ���������� � ���������� �� ��������
		this->contentAfterSortingAndResearch = initialContent;

		// �������� ������
		sortData();
	}

	// �������� ������
	searchingQueries[index] = query;
}

#pragma region �������

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
	// ���� ������ ������
	if (this->listOfInnerMenuItems.empty())
	{
		this->listOfInnerMenuItems.push_back("����������");
		this->listOfInnerMenuItems.push_back("�����");
		this->listOfInnerMenuItems.push_back("�����");
	}
}

void WorkWithIngredientTableMenuState::setListOfColumnFilters()
{
	// ���� ������ ������
	if (this->listOfColumnFilters.empty())
	{
		this->listOfColumnFilters.push_back("� ��");
		this->listOfColumnFilters.push_back("� ��");
		this->listOfColumnFilters.push_back("���");
		this->listOfColumnFilters.push_back("���� ��");
		this->listOfColumnFilters.push_back("���� ��");
		this->listOfColumnFilters.push_back("������ 1");
		this->listOfColumnFilters.push_back("������ 2");
		this->listOfColumnFilters.push_back("��� - �� ��");
		this->listOfColumnFilters.push_back("��� - �� ��");
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

	// ��������� �������� �������
	int page = FIRST_PAGE;
}

#pragma endregion �������

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
	int xCoordForColon = xCoordForFilterValue - COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE;

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

void WorkWithIngredientTableMenuState::workWithTable()
{
	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem(this->listOfInnerMenuItems, STANDARD_CURSOR_X_COORD);

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
	}
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

		// ������ �����
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumnforSorting, orderOfSorting, AlchemicalUserInterface::TableCode::IngredientTable);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}

		// ���� ������� �� ������
		if(contentAfterSortingAndResearch.size() > 0) 
			sortData();

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::IngredientTable, page, numberOfColumnforSorting, orderOfSorting);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setExitFlag(false);

			return;
		}
	}
}

void WorkWithIngredientTableMenuState::sortData()
{
	// ���� �������� ��������
	if (numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_1 || numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_3 || numberOfColumnforSorting == INGREDIENT_TABLE_DIGIT_COLUMN_6)
		this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());

	else
		// ���������
		this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
}

void WorkWithIngredientTableMenuState::launchFilterMenu()
{
	// ������� ���������� Y ���������� ��
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	printFilterItems(this->listOfColumnFilters);

	while (this->alchemicalUserInterface->getExitFlag() != true)
	{
		int page = FIRST_PAGE;

		int numberOfSearchingQuery = 0;

		// ������ �� ����������
		string queryForFiltration = "";

		bool isString = true;

		this->ingredientTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// �������� ����� ���� ����������
		chooseMenuItem(this->listOfColumnFilters, X_COORD_FOR_FILTER_ITEMS);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
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

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getExitFlag() == true)
		{
			// ���������� ����
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

	// �������� �������
	vector<vector<string>> bufferContent;

	for (int i = 0; i < size; ++i)
	{
		// ������ ������������ �������
		int index = 0;

		// ������ ������� � ������� ��������
		int indexOfQuery = 0;

		bool success = false;

		for (int j = 0; j < numberOfColumns; ++j)
		{
			bool isInt = false;
			int intValue = 0;

			if(indexOfQuery != (FILTER_NAME_3 - 1) && indexOfQuery != (FILTER_EFFECT_6 - 1) && indexOfQuery != (FILTER_EFFECT_7 - 1) || searchingQueries[indexOfQuery] != "")
				isInt = tryParseToInt(searchingQueries[indexOfQuery]);

			// ���� ������� ������ ��� �����
			if (isInt == true)
			{
				int min = 0;

				intValue = stoi(contentAfterSortingAndResearch[i][j]);

				// ���� ������ ������ �� ������
				if (this->searchingQueries[indexOfQuery] != "")
				{
					min = stoi(this->searchingQueries[indexOfQuery]);
				}

				++indexOfQuery;

				int max = MAX_INT;

				// ���� ������ ������ �� ������
				if (this->searchingQueries[indexOfQuery] != "")
				{
					max = stoi(this->searchingQueries[indexOfQuery]);
				}

				++indexOfQuery;

				// ���� ����� �� �������� � ��������, �� ������� �� �����
				if (min > intValue || intValue > max)
				{
					success = false;
					break;
				}

				success = true;
			}

			else
			{
				// ���� ������� �� ���������
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