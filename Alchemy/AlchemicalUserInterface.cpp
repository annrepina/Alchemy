#include "AlchemicalUserInterface.h"

string AlchemicalUserInterface::listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"����������",
	"������ ���������� � ���������"
};

// �������� �������� ���� "������� � ����������"
string AlchemicalUserInterface::listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS] = {
	"�������� �����",
	"������� ������������",
	"������� ������������",
	"�������� ������������",
	"������� �����",
	"������ � ���������"
};

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"�����",
	"����� �� ���������"
};

string AlchemicalUserInterface::listOfBuyingIngredientsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"������� ������������ �� ���������� ������",
	"������� ����� ������������, ������� ��� � ������"
};

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
	this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->instructionsXCoord = 0;
	this->instructionsMenuTitle = "���������� � ��������� \"������������\"";
	this->mainMenuTitle = "������� ����";
	this->alchemicalMenuTitle = "���� �������";
	this->buyingIngredientsMenuTitle = "������� ������������";
}

void AlchemicalUserInterface::launchMainLoop()
{
	fillAllMenu();

	// �������� ����������������
	//setXCoord();

	printTitle();

	printExitButton();

	cout << endl;

	printAlchemist();

	//this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	menuCode = MenuCode::MainMenu;

	printMenuInLoop(mainMenu, mainMenuTitle);

	printBye();
}

void AlchemicalUserInterface::chooseMenuItem(map <int, string> menu)
{
	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	do {
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_UP:
			{
				// ��������� ���������
				checkArrowsChoice(boundaryYCoord, VK_UP, menu);
			}
			break;

			case VK_DOWN:
			{
				// ��������� ���������
				checkArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
			}
			break;

			case VK_RETURN:
			{
				// ������� ����� ������ ����
				makeChoice();// !! ������������� ��������
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag);
}

void AlchemicalUserInterface::makeChoice()
{
	switch (menuCode)
	{
		case MenuCode::MainMenu:
		{
			checkChoiceInMainMenu();
		}
		break;

		case MenuCode::AlchemicalMenu:
		{
			checkChoiceInAlchemicalMenu();
		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkChoiceInInstructionsMenu();
		}
		break;

		case MenuCode::BuyingIngredientsMenu:
		{
			checkChoiceInBuyingIngredientsMenu();
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInMainMenu()
{
	switch (this->currentYCursorCoord)
	{
		case MainMenuCode::DoAlchemy:
		{
			doAlchemy();
		}
		break;

		case MainMenuCode::ReadInstructions:
		{
			printInstructions();
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInInstructionsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case InstructionsMenuCode::Return:
		{
			this->menuCode = MenuCode::MainMenu;
			this->currentYCursorCoord = MAIN_MENU_Y_COORD;
			//this->boundaryYCoord = MAIN_MENU_Y_COORD;

			eraseScreenAfterAlchemist();

			printMenuInLoop(mainMenu, mainMenuTitle);
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInAlchemicalMenu()
{
	switch (this->currentYCursorCoord)
	{
		case AlchemicalMenuCode::MakingPotions:
		{

		}
		break;

		case AlchemicalMenuCode::BuyingIngredients:
		{
			buyIngredients();
		}
		break;
	}
}

void AlchemicalUserInterface::checkChoiceInBuyingIngredientsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case 
	}
}

void AlchemicalUserInterface::doAlchemy()
{
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::AlchemicalMenu;

	printMenuInLoop(alchemicalMenu, alchemicalMenuTitle);
}

void AlchemicalUserInterface::buyIngredients()
{
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::BuyingIngredientsMenu;

	printMenuInLoop(buyingIngredientsMenu, alchemicalMenuTitle);
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void AlchemicalUserInterface::fillAllMenu()
{
	mainMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);
	instructionsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);
	buyingIngredientsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingIngredientsMenuItems);
}

void AlchemicalUserInterface::printTitle()
{
	titleXCoord = calculateXCoordInMiddle(title);

	printFramedText(title, TITLE_Y_COORD, titleXCoord);
}

void AlchemicalUserInterface::printExitButton()
{
	// ����� ������
	string exit = "ESC - �����";

	// ���������� ������ ������
	int xCoord = calculateConsoleWidth() - exit.length();

	// ������ ������
	cout << goToXY(EXIT_Y_COORD, xCoord) << exit << endl;
}

void AlchemicalUserInterface::printMenuInLoop(map<int, string> menu, string menuTitle)
{
	printMenuTitle(menuTitle);

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenu(menu);

	cout << goToXY(currentYCursorCoord, STANDARD_CURSOR_X_COORD);
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	//eraseScreenAfterAlchemist();

	//this->instructionsXCoord = calculateXCoordInMiddle(instructionsMenuTitle);

	//cout << goToXY(Y_COORD_AFTER_ALCHEMIST, instructionsXCoord);

	//printColoredText(instructionsMenuTitle, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	//cout << endl;

	menuCode = MenuCode::InstructionsMenu;
	
	//this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	//this->boundaryYCoord = INSTRUCTIONS_Y_COORD;

	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	printMenuInLoop(instructionsMenu, instructionsMenuTitle);
}

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("�� ������ �������!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

void AlchemicalUserInterface::printAlchemist()
{
	// ������!

	string name;

	// ���� ���� ������ � ��� ������
	if ("" == this->alchemist->getName())
	{
		cout << "������� ���� ���: ";
		cin >> name;
	}

	this->alchemist->setName(name);

	eraseScreenAfterTitle();

	this->alchemist->print();
}

void AlchemicalUserInterface::printMenuTitle(string title)
{
	eraseScreenAfterAlchemist();

	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	cout << endl;
}
