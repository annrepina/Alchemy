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

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
	this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
}

void AlchemicalUserInterface::launchMainLoop()
{
	mainMenu = fillActionMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillActionMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);

	// �������� ����������������
	//setXCoord();

	printTitle();

	printExitButton();

	cout << endl;

	printAlchemist();

	printMenuInLoop(mainMenu);



	//printMenu();

	this->func = std::bind(&AlchemicalUserInterface::isMenuChoiceFalse, this, _1);

	checkMenuChoice();

	eraseScreenAfterTitle();

	switch (this->keyBoard->getPressedKey())
	{
	case VK_1: case VK_NUMPAD1:
	{
		doAlchemy();
	}
	break;

	case VK_2: case VK_NUMPAD2:
	{
		cout << "\n����������" << endl;
	}
	break;

	case VK_ESCAPE:
	{
		cout << "\n�� ������ �������!" << endl;
	}
	break;
	}
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
			checkArrowsChoice(MENU_Y_COORD, VK_UP, menu);
		}
		break;

		case VK_DOWN:
		{
			// ��������� ���������
			checkArrowsChoice(MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, menu);
		}
		break;

		case VK_RETURN:
		{
			// !! ������������� ��������

		}
		break;

		case VK_ESCAPE:
			break;
		}
	} while (false == exitFlag);
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

void AlchemicalUserInterface::printTitle()
{
	this->setXCoord();

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

	//// �������� ���� ���� �� �����
	//cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	//cout << "�������� ��������: " << endl;

	//cout << resetColorParams();

	//// ������ �������� ���������� Y
 //   this->currentYCursorCoord = MENU_Y_COORD;

	printMenu(menu);

	//<< "�������� �����" << endl
	//<< "������� ������������" << endl
	//<< "������� ������������" << endl
	//<< "������� �����" << endl
	//<< "������ � ��������" << endl;

	cout << goToXY(currentYCursorCoord, X_STANDARD_CURSOR_COORD);

	//// ���������� ������� ���������� �������
	//this->currentXCursorCoord = 1;
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	eraseScreenAfterTitle();

	cout << "���������� � ��������� \"������������\"" << endl
		<< "0 - �����"
		<< "ESC - �����";
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

	cout << goToXY(MENU_Y_COORD, 1);

	//// ���������� ������� ���������� �������
	//this->currentXCursorCoord = 1;
	this->currentYCursorCoord = MENU_Y_COORD;

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
			checkArrowsChoice(MENU_Y_COORD, VK_UP, alchemicalMenu);

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
			checkArrowsChoice(MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN, alchemicalMenu);
		}
		break;

		case VK_RETURN:
		{
			if (MENU_Y_COORD == this->currentYCursorCoord)
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
