#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

#define DEBUG

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "�������� �����";
    this->goToTitle = "������� �����";
    this->numberOfStates = 1;
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

	// ���� ���-�� ��������� ������������ ������ ����, �� ���������� �� ������
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING)
	{
		error = "��� �������� ����� � ��� ������������ ������������.\n��������� ����-������ � �������.\nESC - �����";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	string choiceFirstIngredient = "������� � ������� �����������: ";

	string choiceSecondIngredient = "������� � ������� �����������: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ����� 
	PotionTable* potionsTable = alchemyLogic->getPotionTable();

	while (false == success)
	{
		printMenu(choiceFirstIngredient, choiceSecondIngredient);

		// ��������� �������� �������
		int page = FIRST_PAGE;

		// �������� ������� ��������� ������������
		this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		// ���� ��� ����� esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			exitMenu();

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

		string name = "";
		int price = 0;
		int power = 0;

		// ���� ����� �� ���������
		if (potion->getEffectId() > 0)
		{
			// ��� �����
			name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

			price = potion->getPrice();

			power = potion->getPower();

			// �������� �����, ���� �� ����� ���
			this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

			// ���������� ����������� �� ��������� ��������� �������� ��������
			firstIngredient->notify(firstIngredientId, NOT_NEW_ELMENT);
			secondIngredient->notify(secondIngredientId, NOT_NEW_ELMENT);

			string congratulations = "�� ������� ����� - " + name + ". ���� - " + to_string(price) + " ����. �������� - " + to_string(power) + ".";

			printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

			// ���� ������� ����� �������
			char a = _getch();

			break;
		}

		// ���� ����� �� ����������
		else
		{
			error = "� ���������, ����� �� ����������!";

			printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

			error = "";
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

void CreatingPotionsMenuState::printMenu(string choiceFirstIngredient, string choiceSecondIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

//int CreatingPotionsMenuState::printChoiceId(int yCoord, int xCoord)
//{
//	// ��������� �� ���������� ��� ����� ������� id
//	cout << goToXY(yCoord, xCoord);
//
//	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);
//
//	return ingredientId;
//}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId)
{
	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// ��������� ���-�� ������������
	alchemyLogic->decreaseNumberOfIngredient(firstIgredientId, 1);

	alchemyLogic->decreaseNumberOfIngredient(secondIngredientId, 1);
}

void CreatingPotionsMenuState::checkIngredientsId(int& firstIngredientId, int& secondIngredientId)
{
	int firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(firstIngredientId);
	int secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(secondIngredientId);

	while (firstIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(firstIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		checkIdForEquality(firstIngredientId, secondIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(firstIngredientId);
	}

	while (secondIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(secondIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		checkIdForEquality(secondIngredientId, firstIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(secondIngredientId);
	}
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1);
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "� ��� ��� ����������� � ������� " + to_string(ingredientId) + ", �������� ������ �����: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void CreatingPotionsMenuState::checkIdForEquality(int& firstIngredientId, int secondIngredientId, int YCoord)
{
	// ���� ����� ���������� �����������
	while (firstIngredientId == secondIngredientId)
	{
		string textOfError = "�� ��� ������� ���������� � ������� " + to_string(firstIngredientId) + ", �������� ������ �����: ";

		printErrorAndMakeChoiceAgain(YCoord, textOfError, firstIngredientId);
	}
}

//void CreatingPotionsMenuState::exitMenu()
//{
//	// ���������� ����
//	this->alchemicalUserInterface->setExitFlag(false);
//
//	this->alchemicalUserInterface->setState(this->getNextState());
//}
