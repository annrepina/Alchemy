#include "CreatingPotionsMenuState.h"
#include "AlchemicalMenuState.h"
#include "AlchemicalUserInterface.h"

//#define DEBUG

CreatingPotionsMenuState::CreatingPotionsMenuState()
{
}

CreatingPotionsMenuState::CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
    this->title = "�������� �����";
    this->goToTitle = "������� �����";
    this->numberOfStates = 1;
}

void CreatingPotionsMenuState::printMenu()
{
    // ���������� ���������� ������ ��� ������ � ����� ������
    currentYCursorCoordState = MAIN_MENU_Y_COORD;

    setListOfCreatingFunctions();

    fillMap<function<MenuState* (CreatingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

    // ����� ������ � ������ ��������� �������
    string error = "";

	// ���� ���-�� ��������� ������������ ������ ����, �� ���������� �� ������
	if (this->alchemicalUserInterface->getIngredientsTablePrinter()->getNumberOfAvailableContent() < MINIMUM_NUMBER_OF_INGREDIENTS_FOR_CREATING)
	{
		error = "��� �������� ����� � ��� ������������ ������������.\n��������� ����-������ � �������.\nESC - �����";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	string choiceFirstIngredient = "������� � ������� �����������: ";
	string choiceSecondIngredient = "������� � ������� �����������: ";
	string choiceNumberOfPoition = "������� ������� ������ ������� �����: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// �������� ������� ����� 
	PotionTable* potionsTable = alchemyLogic->getPotionTable();

	printMenu(choiceFirstIngredient, choiceSecondIngredient, choiceNumberOfPoition);

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

	int firstIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choiceFirstIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
	int secondIngredientId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_3, choiceSecondIngredient.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);

	int numberOfPotion = printChoiceNumber(Y_COORD_AFTER_MENU_TITLE_4, choiceNumberOfPoition);

	// ���� ����� ���������� �����������
	checkIngredientsId(firstIngredientId, secondIngredientId);

	checkNumberOfIngredients(firstIngredientId, secondIngredientId, numberOfPotion);

	// ��������� ���-�� ��������� ������������
	decreaseNumberOfIngredients(firstIngredientId, secondIngredientId, numberOfPotion);

	// ������ ����������
	Ingredient* firstIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(firstIngredientId);

	// ������ ����������
	Ingredient* secondIngredient = alchemyLogic->getIngredientsTable()->getIngredientById(secondIngredientId);

	// ������� ������ ��������� �����
	vector<Potion*> potions;

	// ��������� ��������� ����� � ������
	for (int i = 0; i < numberOfPotion; ++i)
	{
		Potion* potion = alchemyLogic->createPotion(firstIngredient, secondIngredient);

		potions.push_back(potion);
	}

	string name = "";
	int price = 0;
	int power = 0;

	// ���� ������ ����� �� ���������, �� � ��� ����������
	if (potions[0]->getEffectId() > 0)
	{
		// ����������� ������ �������
		int originalSizeOfPoitionTable = potionsTable->getSize();

		// ������� ������,���� �� �������� ������ ���������� �����
		vector<Potion*> uniquePotions;

		for (int i = 0; i < numberOfPotion; ++i)
		{
			// �������� �����, ���� �� ����� ���
			alchemyLogic->checkPotion(potions[i], uniquePotions);
		}

		// ������ ������� ����� ���������� �����
		int sizeOfPotionTableAfterAdding = potionsTable->getSize();

		// ���-�� ����������� �����
		int numberOfAddedPotions = sizeOfPotionTableAfterAdding - originalSizeOfPoitionTable;

		// ���������� ����������� �� ��������� ��������� �������� ��������
		firstIngredient->notify(firstIngredientId, NOT_NEW_ELEMENT);
		secondIngredient->notify(secondIngredientId, NOT_NEW_ELEMENT);

		int vecSize = uniquePotions.size();

		for (int i = 0; i < vecSize; ++i)
		{
			// ��� �����
			name = alchemyLogic->getEffectsTable()->getEffectByKey(uniquePotions[i]->getEffectId())->getName();

			price = uniquePotions[i]->getPrice();

			power = uniquePotions[i]->getPower();

			string congratulations = "�� ������� ����� - " + name + ". ���� - " + to_string(price) + " ����. �������� - " + to_string(power) + ".";

			printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

			cout << endl;
		}
	}

	// ���� ����� �� ����������
	else
	{
		error = "� ���������, ����� �� ����������!";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_5, STANDARD_CURSOR_X_COORD, error);
	}

	// ���� ������� ����� �������
	char a = _getch();
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

void CreatingPotionsMenuState::printMenu(string choiceFirstIngredient, string choiceSecondIngredient, string choiceNumberOfIngredients)
{
	printMenuTitle();

	printColoredTextByCoords(choiceFirstIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);
	printColoredTextByCoords(choiceSecondIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);
	printColoredTextByCoords(choiceNumberOfIngredients, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);
}

void CreatingPotionsMenuState::decreaseNumberOfIngredients(int firstIgredientId, int secondIngredientId, int number)
{
	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// ��������� ���-�� ������������
	alchemyLogic->decreaseNumberOfIngredient(firstIgredientId, number);
	alchemyLogic->decreaseNumberOfIngredient(secondIngredientId, number);
}

void CreatingPotionsMenuState::checkIngredientsId(int& firstIngredientId, int& secondIngredientId)
{
	int firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(firstIngredientId);
	int secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(secondIngredientId);

	while (firstIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(firstIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		checkIdForEquality(firstIngredientId, secondIngredientId, Y_COORD_AFTER_MENU_TITLE_2);

		firstIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(firstIngredientId);
	}

	while (secondIndex == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(secondIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		checkIdForEquality(secondIngredientId, firstIngredientId, Y_COORD_AFTER_MENU_TITLE_3);

		secondIndex = this->alchemicalUserInterface->getIngredientsTablePrinter()->getTable()->findElementInAvailableElements(secondIngredientId);
	}
}

void CreatingPotionsMenuState::checkNumberOfIngredients(int firstIngredientId, int secondIngredientId, int &numberOfPotion)
{
	// �����������, ���������� �� id 
	Ingredient* firstIngredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(firstIngredientId);
	Ingredient* secondIngredient = this->alchemicalUserInterface->getAlchemyLogic()->getIngredientsTable()->getIngredientById(secondIngredientId);

	int numberOfFirstIngredient = firstIngredient->getNumber();
	int numberOfSecondIngredient = secondIngredient->getNumber();

	int newNumber = numberOfPotion;
	int numberOfIngredient;

	// ���������� ���������� ���-��
	if (numberOfFirstIngredient < numberOfSecondIngredient)
	{
		while (numberOfFirstIngredient < newNumber)
		{
			numberOfIngredient = numberOfFirstIngredient;

			printErrorAboutNumberAndMakeChoiceAgain(firstIngredientId, newNumber, numberOfIngredient, Y_COORD_AFTER_MENU_TITLE_4);

			newNumber = numberOfIngredient;
		}
	}

	else
	{
		while (numberOfSecondIngredient < newNumber)
		{
			numberOfIngredient = numberOfSecondIngredient;

			printErrorAboutNumberAndMakeChoiceAgain(secondIngredientId, newNumber, numberOfIngredient, Y_COORD_AFTER_MENU_TITLE_4);

			newNumber = numberOfIngredient;
		}
	}

	numberOfPotion = newNumber;
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& ingredientId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	ingredientId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::IngredientTable);
}

void CreatingPotionsMenuState::printErrorAndMakeChoiceAgain(int& ingredientId, int yCoord)
{
	string textOfError = "� ��� ��� ����������� � ������� " + to_string(ingredientId) + ", �������� ������ �����: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, ingredientId);
}

void CreatingPotionsMenuState::printErrorAboutNumberAndMakeChoiceAgain(int ingredientId, int previousNumber, int& numberOfIngredients, int yCoord)
{
	string textOfError = "� ��� ��� ������ ���������� (" + to_string(previousNumber) + ") ����������� � ������� " + to_string(ingredientId) + ", ������� ������� ���������� : ";

	printErrorAboutNumberAndMakeChoiceAgain(yCoord, textOfError, numberOfIngredients);
}

void CreatingPotionsMenuState::printErrorAboutNumberAndMakeChoiceAgain(int yCoord, string textOfError, int& numberOfIngredients)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	numberOfIngredients = printChoiceNumber(yCoord, textOfError);
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