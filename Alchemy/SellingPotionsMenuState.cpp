#include "SellingPotionsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingPotionsMenuState::SellingPotionsMenuState()
{
}

SellingPotionsMenuState::SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������� �����";
	this->goToTitle = "������� �����";
	this->numberOfStates = 1;
}

//SellingPotionsMenuState::~SellingPotionsMenuState()
//{
//	clear();
//}

void SellingPotionsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (SellingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// ����� ������ � ������ ��������� �������
	string error = "";

	string choiceIngredient = "������� � �����: ";

	string choiceNumberOfIngredient = "������� ���-�� �����: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ������������ 
	//IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (true)
	{
		// ���� ���-�� ��������� ����� ������ ������, �� ������� ������ �� ������
		if (this->alchemicalUserInterface->getPotionTablePrinter()->getNumberOfLines() < MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING)
		{
			error = "� ��� ������ ��� �����.\n�������� ���-������\.\nESC - �����";

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
		//this->alchemicalUserInterface->printTableWithAvailableToUserElements(AlchemicalUserInterface::TableCode::IngredientTable, page);

		this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::PotionTable, page);

		// ���� ��� ����� esc
		if (true == this->alchemicalUserInterface->getExitFlag())
		{
			exitMenu();

			return;
		}

		//int ingredientId = printChoiceIngredientId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		//int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);

		//// ���� ����� ������������� id
		//checkIngredientsId(ingredientId);

		//checkNumberOfIngredient(numberOfIngredient, ingredientId);

		//alchemyLogic->sellIngredient(ingredientId, numberOfIngredient);

		//string congratulations = "�� �������� ��������!";

		//cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		//printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		//// ���� ������� ����� �������
		//char a = _getch();

		//break;
	}
}

MenuState* SellingPotionsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingPotionsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void SellingPotionsMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&SellingPotionsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* SellingPotionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void SellingPotionsMenuState::printMenu(string choicePotion, string choiceNumberOfPotions)
{
	printMenuTitle();

	printColoredTextByCoords(choicePotion, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceNumberOfPotions, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}


