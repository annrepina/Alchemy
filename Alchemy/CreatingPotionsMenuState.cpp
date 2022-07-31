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

	string choiceFirstIngredient = "������� � ������� �����������: ";

	string choiceSecondIngredient = "������� � ������� �����������: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ������������ 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (false == success)
	{
		printMenu(error, choiceFirstIngredient, choiceSecondIngredient);

		// ��������� �������� �������
		int page = FIRST_PAGE;

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

		int firstIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1);

		int secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, choiceSecondIngredient.size() + 1);

		// ���� ����� ���������� �����������
		checkIngredientsId(firstIngredientId, secondIngredientId);

		// ��������� ���-�� ��������� ������������
		decreaseNumberOfIngredients(firstIngredientId, secondIngredientId);

		// ������ ����������
		Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(firstIngredientId);

		// ������ ����������
		Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);

		Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		// ��� �����
		string name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

		int price = potion->getPrice();

		int power = potion->getPower();

		success = this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

		// ���� ����� �� ����������
		if (!success)
		{
			error = "� ���������, ����� �� ����������!";
		}
		else
		{
			cout << "�� ������� ����� - " << name << ". ���� - " << price << " ����." << " �������� - " << power << ".";

			break;
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

void CreatingPotionsMenuState::printMenu(string error, string choiceFirstIngredient, string choiceSecondIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

int CreatingPotionsMenuState::printChoiceId(int yCoord, int xCoord)
{
	// ��������� �� ���������� ��� ����� ������� id
	cout << goToXY(yCoord, xCoord);

	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

	return ingredientId;
}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId)
{
	// �������� ���� �������
	IngredientsTable* ingredientTable = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable();

	// ��������� ���-�� ������������
	ingredientTable->decreaseNumberOfIngredient(firstIgredientId);

	ingredientTable->decreaseNumberOfIngredient(secondIngredientId);
}

void CreatingPotionsMenuState::checkIngredientsId(int firstIngredientId, int& secondIngredientId)
{
	// ���� ����� ���������� �����������
	while (firstIngredientId == secondIngredientId)
	{
		string textOfError = "�� ��� ������� ���������� � ������� " + to_string(secondIngredientId) + "�������� ������ ����� �����: ";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, 1, textOfError);

		secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, textOfError.size() + 1);
	}
}
