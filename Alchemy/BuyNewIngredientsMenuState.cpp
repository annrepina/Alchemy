#include "BuyNewIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState()
{
}

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "������� ������������, ������� ��� � \"������� �������\"";
    this->goToTitle = "������ �����������, ������� ��� � \"������� �������\"";
    this->numberOfStates = 0;
}

void BuyNewIngredientsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	string ingredientName = "";

	// ����� ������ � ������ ��������� �������
	string error = "";

	// ������ �� ������ ����������
	bool success = false;

	//// ������ ������� ��������
	//builder.setEffectsTable(this->alchemicalUserInterface->getAlchemyLogic()->getEffectsTable());

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyNewIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	while (false == success)
	{
		string inputName = "������� �������� �����������: ";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		//cout << inputName;

		cin >> ingredientName;

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryAddNewIngredientToTable(ingredientName);

		if (!success)
		{
			error = "���������� � ������ \"" + ingredientName + "\" ��� ����������, ���������� �����:";
		}

		cout << "������� ������ �� �";
	}




	



		string choiceNumber = "������� ���-�� ������������: ";

		// ���� ���� ������ �� �����
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// ���� ��� ����� esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			// ���������� ����
			this->alchemicalUserInterface->setExitFlag(false);

			this->alchemicalUserInterface->setState(this->getNextState());

			return;
		}

		int id = this->alchemicalUserInterface->chooseId(inputName, AlchemicalUserInterface::TableCode::IngredientTable);

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable);

		success = this->alchemicalUserInterface->tryAddIngredientFromList(id, number);

		// ���� ������� �� ����������
		if (!success)
		{
			error = "������������ �����, ���������� �����:";
		}
	//}
}

MenuState* BuyNewIngredientsMenuState::getNextState()
{
    return nullptr;
}

void BuyNewIngredientsMenuState::setListOfStates()
{
}

void BuyNewIngredientsMenuState::setListOfCreatingFunctions()
{
}
