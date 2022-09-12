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

void SellingPotionsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (SellingPotionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	// ����� ������ � ������ ��������� �������
	string error = "";
	string choicePotion = "������� � �����: ";
	string choiceNumberOfPotion = "������� ���-�� �����: ";

	// �������� ���� ������
	AlchemyLogic* alchemyLogic = this->alchemicalUserInterface->getAlchemyLogic();

	// ���� ���-�� ��������� ����� ������ ������, �� ������� ������ �� ������
	if (this->alchemicalUserInterface->getPotionTablePrinter()->getNumberOfLines() < MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING)
	{
		error = "� ��� ������ ��� �����.\n�������� ���-������\.\nESC - �����";

		printMenuTitle();

		printColoredTextByCoords(error, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

		this->alchemicalUserInterface->chooseExit();

		goBack();

		return;
	}

	printMenu(choicePotion, choiceNumberOfPotion);

	// ��������� �������� �������
	int page = FIRST_PAGE;

	this->alchemicalUserInterface->printTablePagesInLoop(AlchemicalUserInterface::TableCode::PotionTable, page);

	// ���� ��� ����� esc
	if (true == this->alchemicalUserInterface->getWasExit())
	{
		goBack();

		return;
	}

	int potionId = printChoiceId(Y_COORD_AFTER_MENU_TITLE_2, choicePotion.size() + 1, (int)AlchemicalUserInterface::TableCode::PotionTable);

	int numberOfPotion = this->alchemicalUserInterface->chooseNumber(choiceNumberOfPotion, Y_COORD_AFTER_MENU_TITLE_3);

	// ���� ����� ������������� id
	checkPotionId(potionId);
	checkNumberOfPotion(numberOfPotion, potionId);

	alchemyLogic->sellPotion(potionId, numberOfPotion);

	// ������� �������������
	this->alchemicalUserInterface->getPotionTablePrinter()->calculateData();

	string congratulations = "�� �������� ��������!";

	cout << goToXY(Y_COORD_AFTER_MENU_TITLE_4, STANDARD_CURSOR_X_COORD);

	printColoredText(congratulations, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	// ���� ������� ����� �������
	char a = _getch();
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

void SellingPotionsMenuState::printErrorAndMakeChoiceAgain(int& potionId, int yCoord)
{
	string textOfError = "� ��� ��� ����� � ������� " + to_string(potionId) + ", �������� ������ �����: ";

	printErrorAndMakeChoiceAgain(yCoord, textOfError, potionId);
}

void SellingPotionsMenuState::printErrorAndMakeChoiceAgain(int yCoord, string textOfError, int& potionId)
{
	this->alchemicalUserInterface->printError(yCoord, STANDARD_CURSOR_X_COORD, textOfError);

	potionId = printChoiceId(yCoord, textOfError.size() + 1, (int)AlchemicalUserInterface::TableCode::PotionTable);
}

void SellingPotionsMenuState::checkPotionId(int& potionId)
{
	int index = this->alchemicalUserInterface->getPotionTablePrinter()->findElementInAvailableElementsId(potionId);

	while (index == NO_POSITION)
	{
		printErrorAndMakeChoiceAgain(potionId, Y_COORD_AFTER_MENU_TITLE_2);

		index = this->alchemicalUserInterface->getIngredientsTablePrinter()->findElementInAvailableElementsId(potionId);
	}
}

void SellingPotionsMenuState::checkNumberOfPotion(int& numberOfPotion, int potionId)
{
	int currentNumber = this->alchemicalUserInterface->getAlchemyLogic()->getPotionTable()->getPotionById(potionId)->getNumber();

	while (numberOfPotion > currentNumber)
	{
		string textOfError = "� ��� ��� ������ ���������� ����� � ������� " + to_string(potionId) + ", ������� ������� ����������: ";

		this->alchemicalUserInterface->printError(Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD, textOfError);

		numberOfPotion = this->alchemicalUserInterface->chooseNumber(textOfError, Y_COORD_AFTER_MENU_TITLE_3);
	}
}