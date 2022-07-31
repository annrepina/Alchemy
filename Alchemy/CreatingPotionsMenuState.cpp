#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "�������� �����";
    this->goToTitle = "������� �����";
    this->numberOfStates = 0;
}

//CreatingPotionsMenuState::~CreatingPotionsMenuState()
//{
//    clear();
//}

void CreatingPotionsMenuState::printMenu()
{
    // ���������� ���������� ������ ��� ������ � ����� ������
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (CreatingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

    // ���������� ������� 
    bool success = false;

    // ����� ������ � ������ ��������� �������
    string error = "";

	while (false == success)
	{
		// ��������� �������� �������
		int page = FIRST_PAGE;

		string choiceFirstIngredient = "������� � ������� �����������: ";

		string choiceSecondIngredient = "������� � ������� �����������: ";

		// ���� ���� ������ �� �����
		bool exit = false;

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

		// �������� ������� ��������� ������������
		this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// ���� ��� ����� esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			// ���������� ����
			this->alchemicalUserInterface->setExitFlag(false);

			this->alchemicalUserInterface->setState(this->getNextState());

			return;
		}

		// ��������� �� ���������� ��� ����� ������� id
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1);

		int firstIngredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

		// ��������� �� ���������� ��� ����� ������� id
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_3, choiceFirstIngredient.size() + 1);

		int secondIngredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

		// ���� ����� ���������� �����������
		if (firstIngredientId == secondIngredientId)
		{
			string textOfError = "�� ��� ������� ���������� � ������� " + to_string(secondIngredientId) + "�������� ������ ����� �����: ";

			this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, 1, textOfError);
		}



		//success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(firstIngredient, number);

		// ���� ������� �� ����������
		if (!success)
		{
			error = "������������ �����, ���������� �����:";
		}
	}
}

MenuState* CreatingPotionsMenuState::getNextState()
{
    return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void CreatingPotionsMenuState::setListOfStates()
{
    this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void CreatingPotionsMenuState::setListOfCreatingFunctions()
{
    // ���� ������ ������
    if (this->listOfCreatingFunctions.empty())
    {
        this->listOfCreatingFunctions.push_back(&CreatingPotionsMenuState::createReturnMenuState);
    }
}

ReturnMenuState* CreatingPotionsMenuState::createReturnMenuState()
{
    return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
