#include "BuyNewIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState()
{
}

BuyNewIngredientsMenuState::BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "������� ������������, ������� ��� � \"������� �������\"";
    this->goToTitle = "������ �����������, ������� ��� � \"������� �������\"";
    this->numberOfStates = 1;
}

void BuyNewIngredientsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	// ����� ������ � ������ ��������� �������
	string error = "";

	// ������ �� ������ ���������� (������� �� �����)
	bool success = false;

	// ������ ����������� ��� ���?
	bool tryAddNewIngredient = false;

	//// ������ ������� ��������
	//builder.setEffectsTable(this->alchemicalUserInterface->getAlchemyLogic()->getEffectsTable());

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (BuyNewIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	while (false == success)
	{
		string ingredientName;

		// id �����������
		int ingredientId;

		Ingredient* ingredient;

		printMenuTitle();

		string inputName = "������� �������� �����������: ";

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		printColoredTextByCoords(inputName, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

		//cout << inputName;

		//cin.getline()

		//std::string name;
		//std::cout << "Input name: ";
		std::cin.ignore(1, '\n');
		getline(std::cin, ingredientName);

		//ingredientName = std::getline(std::cin, ingredientName);

		//cin.getline(ingredientName, 25, '\n');

		//getline(cin, ingredientName, '\n');

		//cin >> ingredientName;

		// ������ �� �������� ����� ����������
		tryAddNewIngredient = this->alchemicalUserInterface->getAlchemyLogic()->tryAddNewIngredientToTable(ingredientName);

		// ���� ��������, ������ ����� ���������� � ���� ��� ����
		if (!tryAddNewIngredient)
		{
			cout << "� ������� ���� " << ingredientName << ". ";

			// ���� �� ����� ���� ����������
			ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientByName(ingredientName);

			// ������� ���� �����
			//cout << ingredientName << " ����� " << ingredient->getPrice() << " ����." << endl;

			// ������ id �����������
			ingredientId = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIdByIngredient(ingredient);
		}
		else
		{
			ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getEndIterator()->second;

			ingredientId = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getEndIterator()->first;
		}

		// ������� ���� �����
		cout << "���� - " << ingredient->getPrice() << " ����." << endl;

		string choiceNumber = "������� ���-��: ";

		cout << choiceNumber;

		int number = this->alchemicalUserInterface->chooseNumber(choiceNumber, AlchemicalUserInterface::TableCode::IngredientTable, Y_COORD_AFTER_MENU_TITLE_4);

		success = this->alchemicalUserInterface->getAlchemyLogic()->tryBuyIngredientFromList(ingredientId, number);

		// ���� ������� �� ����������
		if (!success)
		{
			error = "������������ �����, ���������� �����:";
			continue;
		}

		cout << "���������� ������!" << endl;
	}

	cout << "Enter - ���������� �������, ESC - �����";

	chooseContinueOrGoBack();

	// ���� ��� ����� ESC, �� ������� �����
	if (this->alchemicalUserInterface->getExitFlag() == true)
	{
		// ���������� ����
		this->alchemicalUserInterface->setExitFlag(false);

		this->alchemicalUserInterface->setState(this->getNextState());
	}
}

MenuState* BuyNewIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void BuyNewIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void BuyNewIngredientsMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&BuyNewIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* BuyNewIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new BuyingIngredientsMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
