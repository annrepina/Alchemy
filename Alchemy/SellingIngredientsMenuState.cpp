#include "SellingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

SellingIngredientsMenuState::SellingIngredientsMenuState()
{
}

SellingIngredientsMenuState::SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "������� ������������";
	this->goToTitle = "������� �����������";
	this->numberOfStates = 0;
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

	// ���������� ������� 
	bool success = false;

	// ����� ������ � ������ ��������� �������
	string error = "";

	// ���� ���-�� ��������� ������������ ������ ������, �� ������� ������ �� ������
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
	{
		error = "��� ������� ������������ � ��� ������������ ������������.\n��������� ����-������ � �������.\nESC - �����";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		exitMenu();

		return;
	}

	string choiceIngredient = "������� � �����������: ";

	string choiceNumberOfIngredient = "������� ���-�� �����������: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ������������ 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	while (false == success)
	{
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

		int ingredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1);

		int numberOfIngredient = this->alchemicalUserInterface->chooseNumber(choiceNumberOfIngredient, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_3);

		//// ���� ����� ���������� �����������
		//checkIngredientsId(ingredientId, secondIngredientId);

		//// ��������� ���-�� ��������� ������������
		//decreaseNumberOfIngredients(ingredientId, secondIngredientId);

		//// ������ ����������
		//Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(ingredientId);

		//// ������ ����������
		//Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);


		//Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		//string name = "";
		//int price = 0;
		//int power = 0;

		//// ���� ����� �� ���������
		//if (potion->getEffectId() > 0)
		//{
		//	// ��� �����
		//	name = alchemyLogic->getEffectsTable()->getEffectByKey(potion->getEffectId())->getName();

		//	price = potion->getPrice();

		//	power = potion->getPower();

		//	// ���������� ����������� �� ��������� ��������� �������� ��������
		//	firstIngredient->notify(ingredientId);
		//	secondIngredient->notify(secondIngredientId);
		//}

		//success = this->alchemicalUserInterface->getAlchemyLogic()->checkPotion(potion);

		//// ���� ����� �� ����������
		//if (!success)
		//{
		//	error = "� ���������, ����� �� ����������!";

		//	printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

		//	error = "";
		//}
		//else
		//{
		//	string congratulations = "�� ������� ����� - " + name + ". ���� - " + to_string(price) + " ����. �������� - " + to_string(power) + ".";

		//	//cout << "" << name << ". ���� - " << price << " ����." << " �������� - " << power << ".";

		//	printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

		//	// ���� ������� ����� �������
		//	char a = _getch();

		//	break;
		//}
	}


}

MenuState* SellingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void SellingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new SellingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
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
	return new ReturnMenuState(new SellingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void SellingIngredientsMenuState::printMenu(string choiceIngredient, string choiceNumberOfIngredient)
{
	printMenuTitle();

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	printColoredTextByCoords(choiceNumberOfIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
}

int SellingIngredientsMenuState::printChoiceId(int yCoord, int xCoord)
{
	// ��������� �� ���������� ��� ����� ������� id
	cout << goToXY(yCoord, xCoord);

	int ingredientId = this->alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

	return ingredientId;
}



