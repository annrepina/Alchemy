#include "SellingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingIngredientsMenuState::SellingIngredientsMenuState()
{
}

SellingIngredientsMenuState::SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������� ������������";
	this->goToTitle = "������� �����������";
	this->numberOfStates = 1;
}

//SellingIngredientsMenuState::~SellingIngredientsMenuState()
//{
//	clear();
//}

void SellingIngredientsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (SellingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// ����� ������ � ������ ��������� �������
	string error = "";

	string choiceIngredient = "������� � �����������: ";

	string choiceNumberOfIngredient = "������� ���-�� �����������: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ������������ 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (true)
	{
		// ���� ���-�� ��������� ������������ ������ ������, �� ������� ������ �� ������
		if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
		{
			error = "� ��� ������ ��� ������������.\n��������� ����-������ � �������.\nESC - �����";

			printMenuTitle();

			printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

			this->alchemicalUserInterface->chooseExit();

			exitMenu();

			return;
		}

		printMenu(choiceIngredient, choiceNumberOfIngredient);

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

		int ingredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);

		int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, Y_COORD_AFTER_MENU_TITLE_3);

		// ���� ����� ������������� id
		checkIngredientsId(ingredientId);

		checkNumberOfIngredient(numberOfIngredient, ingredientId);

		alchemyLogic->sellIngredient(ingredientId, numberOfIngredient);

		string congratulations = "�� �������� ��������!";

		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		// ���� ������� ����� �������
		char a = _getch();

		break;
	}
}

MenuState* SellingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void SellingIngredientsMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&SellingIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* SellingIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void SellingIngredientsMenuState::printMenu(string choiceIngredient, string choiceNumberOfIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceNumberOfIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "� ��� ��� ����������� � ������� " + to_string(ingredientId) + ", �������� ������ �����: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void SellingIngredientsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
}

void SellingIngredientsMenuState::checkIngredientsId(int& ingredientId)
{
	int index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);

	while (index == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(ingredientId, Y_COORD_AFTER_MENU_TITLE_2);

		index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(ingredientId);
	}
}

void SellingIngredientsMenuState::checkNumberOfIngredient(int& numberOfIngredient, int ingrdientId)
{
	int currentNumber = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(ingrdientId)->getNumber();

	while (numberOfIngredient > currentNumber)
	{
		string textOfError = "� ��� ��� ������ ���������� ����������� � ������� " + to_string(ingrdientId) + ", ������� ������� ����������: ";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD, textOfError);

		numberOfIngredient = this->alchemicalUserInterface->chooseNumber(textOfError, Y_COORD_AFTER_MENU_TITLE_3);
	}
}