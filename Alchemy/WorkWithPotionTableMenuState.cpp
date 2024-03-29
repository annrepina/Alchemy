#include "WorkWithPotionTableMenuState.h"
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
    this->title = "������ � �������";
    this->goToTitle = "�������� � �������";
    this->numberOfStates = 1;
    this->numberOfColumnforSorting = DEFAULT_NUMBER_OF_COLUMN;
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

	setFields();

	printMenuTitle();

	// ���� ���-�� ��������� ����� ������ ������, �� ����������� ������ �� ������
	if (this->contentAfterSortingAndResearch.size() < MINIMUM_NUMBER_OF_POTIONTS)
	{
		string error = "� ��� ������ ��� �����.\n�������� ���-������.\.\nESC - �����";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems(this->listOfInnerMenuItems);

	printFilterItems(this->listOfColumnFilters);

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	workWithTable();
}

void WorkWithPotionTableMenuState::setContent()
{
	this->initialContent = this->potionTablePrinter->getTableContent();

	this->contentAfterSortingAndResearch = this->initialContent;
}

void WorkWithPotionTableMenuState::setListOfColumnFilters()
{
	// ���� ������ ������
	if (this->listOfColumnFilters.empty())
	{
		this->listOfColumnFilters.push_back("� ��");
		this->listOfColumnFilters.push_back("� ��");
		this->listOfColumnFilters.push_back("���");
		this->listOfColumnFilters.push_back("�������� ��");
		this->listOfColumnFilters.push_back("�������� ��");
		this->listOfColumnFilters.push_back("���� ��");
		this->listOfColumnFilters.push_back("���� ��");
		this->listOfColumnFilters.push_back("��� - �� ��");
		this->listOfColumnFilters.push_back("��� - �� ��");
	}
}

void WorkWithPotionTableMenuState::launchFilterMenu()
{
	// ������� ���������� Y ���������� ��
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	printFilterItems(this->listOfColumnFilters);

	while (this->alchemicalUserInterface->getWasExit() != true)
	{
		int page = FIRST_PAGE;

		int numberOfSearchingQuery = 0;

		// ������ �� ����������
		string queryForFiltration = "";

		bool isString = true;

		this->potionTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// �������� ����� ���� ����������
		chooseMenuItem(this->listOfColumnFilters, X_COORD_FOR_FILTER_ITEMS);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getWasExit() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setWasExit(false);

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

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getWasExit() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setWasExit(false);

			currentYCursorCoordState = MAIN_MENU_Y_COORD + 1;

			return;
		}
	}
}

void WorkWithPotionTableMenuState::launchSortingMenu()
{
	while (this->alchemicalUserInterface->getWasExit() != true)
	{
		int page = FIRST_PAGE;

		this->potionTablePrinter->print(contentAfterSortingAndResearch, page, numberOfColumnforSorting, orderOfSorting);

		// ������ �����
		this->alchemicalUserInterface->chooseColumnAndOrderOfSorting(numberOfColumnforSorting, orderOfSorting, AlchemicalUserInterface::TableCode::PotionTable);

		sortData();

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getWasExit() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setWasExit(false);

			return;
		}

		this->alchemicalUserInterface->printTablePagesInLoopWhileSorting(contentAfterSortingAndResearch, AlchemicalUserInterface::TableCode::PotionTable, page, numberOfColumnforSorting, orderOfSorting);

		// ���� ��� ����� �� ���� ����������, �� �� �������� ������ ���������, � ������� ������ �� ����������
		if (this->alchemicalUserInterface->getWasExit() == true)
		{
			// ���������� ����
			this->alchemicalUserInterface->setWasExit(false);

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
	// ���� �������� ��������
	if (numberOfColumnforSorting != NON_DIGIT_COLUMN)
		this->alchemicalUserInterface->getAlchemyLogic()->sortDigitData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());

	else
		// ���������
		this->alchemicalUserInterface->getAlchemyLogic()->sortStringData(&contentAfterSortingAndResearch[0], numberOfColumnforSorting, orderOfSorting, contentAfterSortingAndResearch.size());
}

void WorkWithPotionTableMenuState::filterData()
{
	int size = contentAfterSortingAndResearch.size();

	int numberOfColumns = this->potionTablePrinter->getNumberOfColumns();

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

			if (indexOfQuery != (FILTER_NAME_3 - 1) || searchingQueries[indexOfQuery] != "")
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