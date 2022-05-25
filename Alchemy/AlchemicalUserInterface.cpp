#include "AlchemicalUserInterface.h"

// �������� �������� ���� "������� � ����������"
string AlchemicalUserInterface::listOfMenuItems[TOTAL_NUMBER_OF_MENU_ITEMS] = {
	"�������� �������� : ",
	"�������� �����",
	"������� ������������",
	"������� ������������",
	"������� �����",
	"������ � ���������"
};

AlchemicalUserInterface::AlchemicalUserInterface()
{
	this->alchemist = new Alchemist();
}

void AlchemicalUserInterface::launchMainLoop()
{
	fillActionMenuMap();

	// �������� ����������������
	//setXCoord();

	printTitle();

	printExitButton();

	printMainMenu();

	this->func = std::bind(&UserInterface::isMenuChoiceFalse, this, _1);

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

void AlchemicalUserInterface::fillActionMenuMap()
{
	// ��������� ����
	int startIndex = ACTION_MENU_Y_COORD;

	// ��������� ������������� ������
	for (int i = 0; i < NUMBER_OF_MAIN_MENU_ITEMS; ++i, ++startIndex)
	{
		this->actionMenu.emplace(startIndex, listOfMenuItems[i]);
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

void AlchemicalUserInterface::printMainMenu()
{
	cout << "\n�������� ��������: " << endl
		<< "1 - ����������" << endl
		<< "2 - ������������ � ����������� � ���������" << endl/*
		<< "ESC - �����" << endl*/;
}

void AlchemicalUserInterface::printInstructions()
{
	eraseScreenAfterTitle();

	cout << "���������� � ��������� \"������������\"" << endl
		<< "0 - �����"
		<< "ESC - �����";
}

void UserInterface::printActionMenu()
{
	// �������� ���� ���� �� �����
	cout << changeBackgroundColorsExtra(R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);

	// ��������� ������ ������ �������� ���� ��������
	int startIndex = 0;

	cout << listOfMenuItems[startIndex++] << endl;
	//cout << "�������� ��������: " << endl;

	cout << resetColorParams();

	// �������� ������ ����
	for (int i = startIndex; i < NUMBER_OF_MAIN_MENU_ITEMS; ++i)
	{
		cout << listOfMenuItems[i] << endl;
	}
	//<< "�������� �����" << endl
	//<< "������� ������������" << endl
	//<< "������� ������������" << endl
	//<< "������� �����" << endl
	//<< "������ � ��������" << endl;

	cout << goToXY(ACTION_MENU_Y_COORD, 1);

	// ���������� ������� ���������� �������
	this->currentXCursorCoord = 1;
	this->currentYCursorCoord = ACTION_MENU_Y_COORD;

	this->func = std::bind(&UserInterface::isArrowKeyFalse, this, _1);

	// ���� ��� ������ �� ����� do-while
	bool exitFlag = false;

	do {
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
		case VK_UP:
		{
			// ��������� ���������
			checkArrowsChoice(exitFlag, ACTION_MENU_Y_COORD, VK_UP);

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
			// ��������� ���������
			checkArrowsChoice(exitFlag, ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS - 1, VK_DOWN);
		}
		break;

		case VK_RETURN:
		{
			if (ACTION_MENU_Y_COORD == this->currentYCursorCoord)
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

bool UserInterface::isContinue(int key)
{
	return VK_RETURN != key && VK_ESCAPE != key;
}

bool UserInterface::isArrowKeyFalse(int key)
{
	bool res = VK_UP != key && VK_DOWN != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

void UserInterface::setXCoord()
{
	titleXCoord = (calculateConsoleWidth() / 2) - (title.length() / 2);
}


void UserInterface::checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode)
{
	// ���������� ����
	exitFlag = false;

	// ���� ��������� ���������� �� ����� �������
	if (BorderYCoord != this->currentYCursorCoord)
	{
		// ���� ������ ����
		if (VK_DOWN == keyCode)
		{
			// �������� ����� ���� ��� ���������
			cout << actionMenu[currentYCursorCoord] << endl;

			// ����������� ����������
			++this->currentYCursorCoord;
		}
		// ���� ������ �����
		else
			// ��������� ����������
			--this->currentYCursorCoord;

		// ��������� �� �����������
		cout << goToXY(this->currentYCursorCoord, 1);

		// �������� ������� ���� ��������
		for (int i = currentYCursorCoord; i < ACTION_MENU_Y_COORD + NUMBER_OF_MAIN_MENU_ITEMS; ++i)
		{
			if (i == currentYCursorCoord)
			{
				printTextWithBackground(actionMenu[i], R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			}

			else
				// �������� ����� ����
				cout << actionMenu[i] << endl;
		}

		// ������������ � ����������
		cout << goToXY(currentYCursorCoord, 1);
	}
}

