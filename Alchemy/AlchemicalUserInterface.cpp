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
	"������� �����",
	"������ � ���������"
};

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"�����",
	"����� �� ���������"
};

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
	this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->instructionsXCoord = 0;
	this->instructionsTitle = "���������� � ��������� \"������������\"";
}

void AlchemicalUserInterface::launchMainLoop()
{
	mainMenu = fillActionMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillActionMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);

	this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	instructionsMenu = fillActionMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);

	// �������� ����������������
	//setXCoord();

	printTitle();

	printExitButton();

	cout << endl;

	printAlchemist();

	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;

	menuCode = MenuCode::MainMenu;

	printMenuInLoop(mainMenu);

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
				checkArrowsChoice(boundaryYCoord + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, menu);
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

		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkChoiceInInstructionsMenu();
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
			this->boundaryYCoord = MAIN_MENU_Y_COORD;

			eraseScreenAfterAlchemist();

			printMenuInLoop(mainMenu);
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::doAlchemy()
{
	//printContinueGameMenu();

// !!! ������ ��, �.�. ���� ����� ��������� !!!

//cout << "������ ���������� ��������� ���� ��� ������� �����?" << endl
//	<< "1 - ���������� ����" << endl
//	<< "2 - ������� ����� ����" << endl;

//func = std::bind(&UserInterface::isContinueGameFalse, this, _1);

//checkMenuChoice();

// !!! ����� ��������
// ��� ��������





// !!! �������� !!!

// ���� ��� ������������ ������
	if ("" == this->alchemist->getName())
	{
		// ��� ������������
		string name;

		cout << "������� ���� ���: ";

		cin >> name;

		this->alchemist->setName(name);
	}



	//string name = "������";

	eraseScreenAfterTitle();

	//this->alchemist->setName(name);

	this->alchemist->print();

	printActionMenu();
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
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

void AlchemicalUserInterface::printMenuInLoop(map<int, string> menu)
{
	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenu(menu);

	cout << goToXY(currentYCursorCoord, STANDARD_CURSOR_X_COORD);
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	//eraseScreenAfterTitle();

	eraseScreenAfterAlchemist();

	this->instructionsXCoord = calculateXCoordInMiddle(instructionsTitle);

	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, instructionsXCoord);

	printColoredText(instructionsTitle, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	cout << endl;

	//printTextWithBackground("�����", R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	menuCode = MenuCode::InstructionsMenu;
	
	this->currentYCursorCoord = INSTRUCTIONS_Y_COORD;
	this->boundaryYCoord = INSTRUCTIONS_Y_COORD;

	printMenuInLoop(instructionsMenu);
}

void AlchemicalUserInterface::printActionMenu()
{
	// �������� ���� ���� �� �����
	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	//// ��������� ������ ������ �������� ���� ��������
	//int startIndex = 0;

	//cout << listOfMenuItems[startIndex++] << endl;
	cout << "�������� ��������: " << endl;

	cout << resetColorParams();

	// �������� ������ ����
	for (int i = 0; i < NUMBER_OF_ALCHEMICAL_MENU_ITEMS; ++i)
	{
		cout << listOfALchemicalMenuItems[i] << endl;
	}
	//<< "�������� �����" << endl
	//<< "������� ������������" << endl
	//<< "������� ������������" << endl
	//<< "������� �����" << endl
	//<< "������ � ��������" << endl;

	cout << goToXY(MAIN_MENU_Y_COORD, 1);

	//// ���������� ������� ���������� �������
	//this->currentXCursorCoord = 1;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;

	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	// ���� ��� ������ �� ����� do-while
	bool exitFlag = false;

	do {
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
		case VK_UP:
		{
			// !! ������������
			// ��������� ���������
			checkArrowsChoice(MAIN_MENU_Y_COORD, VK_UP, alchemicalMenu);

			//if (ACTION_MENU_Y_COORD == this->currentYCursorCoord)
			//{
			//	exitFlag = true;
			//}
			//else
			//{
			//	cout << goToXY(--this->currentYCursorCoord, 1);
			//	// �������� ���� ���� �� �����
			//	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			//	// �������� ������� ���� ��������
			//	for (int i = currentYCursorCoord; i < ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS; ++i)
			//	{
			//		if (i == currentYCursorCoord)
			//		{
			//			// �������� ���� ���� �� �����
			//			cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			//			// �������� ����� ����
			//			cout << actionMenu[i] << endl; 
			//			// ���������� ��������� ������
			//			cout << resetColorParams();
			//		}
			//		else 
			//			// �������� ����� ����
			//			cout << actionMenu[i] << endl;
			//	}
			//	cout << goToXY(currentYCursorCoord, 1);
			//	// ���������� ����
			//	exitFlag = false;
			// }	
		}
		break;

		case VK_DOWN:
		{
			// !! ������������
			// ��������� ���������
			checkArrowsChoice(MAIN_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, alchemicalMenu);
		}
		break;

		case VK_RETURN:
		{
			if (MAIN_MENU_Y_COORD == this->currentYCursorCoord)
			{
				exitFlag = false;
			}

			else
				// !! ������������� ��������
			{

			}
		}
		break;

		case VK_ESCAPE:
			break;
		}
	} while (false == exitFlag);
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
