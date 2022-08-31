#include "WorkWithIngredientTableMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState()
{
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = nullptr;
}

WorkWithIngredientTableMenuState::WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������ � �������������";
	this->goToTitle = "�������� � �������������";
	this->numberOfStates = 1;
	this->numberOfColumn = DEFAULT_NUMBER_OF_COLUMN;
	this->orderOfSorting = ASCENDING_ORDER_OF_SORTING;
	this->ingredientTablePrinter = alchemicalUserInterface->getIngredientsTablePrinter();
}

void WorkWithIngredientTableMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (WorkWithIngredientTableMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	setListOfInnerMenuItems();

	fillMap<string>(innerMenuItems, listOfInnerMenuItems, currentYCursorCoordState, INNER_MENU_ITEMS);

	setContent();

	// ��������� �������� �������
	int page = FIRST_PAGE;

	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	while (this->alchemicalUserInterface->getExitFlag() == false)
	{
		chooseMenuItem();

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

void WorkWithIngredientTableMenuState::setContent()
{
	this->initialContent = this->ingredientTablePrinter->getTableContent();

	this->contentAfterSortingAndSearch = this->initialContent;
}

ReturnMenuState* WorkWithIngredientTableMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new WorkWithTablesMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void WorkWithIngredientTableMenuState::printMenuItems()
{
	int border = this->boundaryYCoord + innerMenuItems.size();

	// �������� ������������� ������
	for (int i = this->currentYCursorCoordState; i < border; ++i)
	{
		if (i == this->currentYCursorCoordState)
		{
			printTextWithBackground(innerMenuItems[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// �������� ����� ����
			cout << innerMenuItems[i] << endl;
	}
}

void WorkWithIngredientTableMenuState::checkVerticalArrowsChoice(int borderYCoord, int keyCode)
{
		// ���� ��������� ���������� �� ����� �������
	if (borderYCoord != this->currentYCursorCoordState)
	{
		// ���� ������ ����
		if (VK_DOWN == keyCode)
		{
			cout << goToXY(currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

			// �������� ����� ���� ��� ���������
			cout << innerMenuItems[currentYCursorCoordState];

			// ����������� ����������
			++this->currentYCursorCoordState;
		}
		// ���� ������ �����
		else
			// ��������� ����������
			--this->currentYCursorCoordState;

		// ��������� �� �����������
		cout << goToXY(this->currentYCursorCoordState, 0);

		printMenuItems();

		// ������������ � ����������
		cout << goToXY(currentYCursorCoordState, 0);
	}
}

void WorkWithIngredientTableMenuState::chooseMenuItem()
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
			this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);

		}
		break;

		case VK_DOWN:
		{
			// ��������� ���������
			this->checkVerticalArrowsChoice(this->boundaryYCoord + innerMenuItems.size() - 1, VK_DOWN);
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
		if (numberOfColumn == COLUMN_1 || numberOfColumn == COLUMN_3 || numberOfColumn == COLUMN_6)
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
