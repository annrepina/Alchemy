#include "EatingIngredientsMenuState.h"
#include "AlchemicalUserInterface.h"

EatingIngredientsMenuState::EatingIngredientsMenuState()
{
}

EatingIngredientsMenuState::EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "����� ����������";
	this->goToTitle = "������ ����������";
	this->numberOfStates = 1;
}
void EatingIngredientsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (EatingIngredientsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// ����� ������ � ������ ��������� �������
	string error = "";

	string choiceIngredient = "������� � �����������: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ������������ 
	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();

	// ���� ���-�� ��������� ������������ ������ ������, �� ������ ������ �� ������
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_SELLING)
	{
		error = "� ��� ������ ��� ������������.\n��������� ����-������ � �������.\nESC - �����";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	printMenuTitle();

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	// ��������� �������� �������
	int page = FIRST_PAGE;

	// �������� ������� ��������� ������������
	this->alchemicalUserInterface->printIngredientsTableWithAvailableToUserElements(page);

	// ���� ��� ����� esc
	if (true == this->alchemicalUserInterface->getWasExit())
	{
		goBack();

		return;
	}

	int ingredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);

	// ���� ����� ������������� id
	checkIngredientsId(ingredientId);

	alchemyLogic->eatIngredient(ingredientId);

	string congratulations = "�� ����� ���������� � ������ ��� ������!";

	cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

	printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	// ���� ������� ����� �������
	char a = _getch();
}

MenuState* EatingIngredientsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void EatingIngredientsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void EatingIngredientsMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&EatingIngredientsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* EatingIngredientsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new AlchemicalMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}

void EatingIngredientsMenuState::checkIngredientsId(int& ingredientId)
{
	int index = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(ingredientId);

	bool wasClosedEff = wasUnknownEffect(ingredientId);

	while (index == NO_POSITION || wasClosedEff == false)
	{
		string error;

		if (index == NO_POSITION)

			error = "� ��� ��� ����������� � ������� " + to_string(ingredientId) + ", �������� ������ �����: ";

		else
			error = "� ����������� � ������� " + to_string(ingredientId) + " ��� ������� �������, �������� ������ �����: ";

		printErrorAndMakeChoiceAgain(Y_COORD_AFTER_MENU_TITLE_2, error, ingredientId);

		// �������������
		index = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(ingredientId);
		wasClosedEff = wasUnknownEffect(ingredientId);
	}
}

void EatingIngredientsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
}

bool EatingIngredientsMenuState::wasUnknownEffect(int ingredientId)
{
	bool wasClosedEffect = false;

	Ingredient* ingredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(ingredientId);

	// �������� �� ������
	auto beginIter = ingredient->getBeginIteratorOfEffectsId();

	// �������� �� �����
	auto endIter = ingredient->getEndIteratorOfEffectsId();

	for (auto i = beginIter; i != endIter; ++i)
	{
		if (i->second == UNKNOWN)
		{
			wasClosedEffect = true;

			break;
		}
	}

	return wasClosedEffect;
}