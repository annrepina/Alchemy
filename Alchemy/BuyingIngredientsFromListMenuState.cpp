#include "BuyingIngredientsFromListMenuState.h"
#include "BuyingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState()
{
	//index = 0;
}

BuyingIngredientsFromListMenuState::BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������� ������������ �� \"������� �������\"";
	this->goToTitle = "������ ����������� �� \"������� �������\"";
	this->numberOfStates = 1;
	//this->index = 0;
}

//BuyingIngredientsFromListMenuState::~BuyingIngredientsFromListMenuState()
//{
//}

void BuyingIngredientsFromListMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	// ���������� ������� 
	bool success = false;

	// ����� ������ � ������ ��������� �������
	string error = "";

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyingIngredientsFromListMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	string choiceIngredient = "������� � �����������: ";
	string choiceNumber = "������� ���-�� ������������: ";
	string successfullBuying = "";

	while (false == success)
	{
		// ��������� �������� �������
		int page = FIRST_PAGE;

		// ���� ���� ������ �� �����
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// ���� ��� ����� esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			exitMenu();

			return;
		}

		// ������� �� ���������� ��� ������
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		int id = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, Y_COORD_AFTER_MENU_TITLE_3);

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(id, number);

		// ���� ������� �� ����������
		if (!success)
		{
			error = "������������ �����, ���������� �����:";
		}
		else
		{
			successfullBuying = "���������� �" + to_string(id) + " ������!";

			cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, 1);

			printColoredText(successfullBuying, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

			// ���� ������� ����� �������
			char a = _getch();
		}
	}
}

MenuState* BuyingIngredientsFromListMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void BuyingIngredientsFromListMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyingIngredientsFromListMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&BuyingIngredientsFromListMenuState::createReturnMenuState);
	}
}

ReturnMenuState* BuyingIngredientsFromListMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

