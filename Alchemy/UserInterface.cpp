#include "UserInterface.h"

UserInterface::UserInterface()
{
	//this->alchemist = nullptr;

	this->titleXCoord = 0;
	this->currentXCursorCoord = 0;
	this->currentYCursorCoord = 0;

	this->keyBoard = this->keyBoard->getInstance();
}

void UserInterface::setTitle(string title)
{
	this->title = title;
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

void UserInterface::eraseScreenAfterTitle()
{
	cout << goToXY(Y_COORD_AFTER_TITLE, 0);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

bool UserInterface::isMenuChoiceFalse(int key)
{
	return key != VK_1 && key != VK_2 && key != VK_NUMPAD1 && key != VK_NUMPAD2 && key != VK_ESCAPE;
}

//bool UserInterface::isContinueGameFalse(int key)
//{
//	return VK_1 != key && VK_2 != key && VK_NUMPAD1 != key && VK_NUMPAD2 != key && key != VK_ESCAPE;
//}

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

//void UserInterface::fillActionMenuMap()
//{
//	// ��������� ����
//	int startIndex = ACTION_MENU_Y_COORD;
//
//	// ��������� ������������� ������
//	for (int i = 0; i < NUMBER_OF_MAIN_MENU_ITEMS; ++i, ++startIndex)
//	{
//		this->actionMenu.emplace(startIndex, listOfMenuItems[i]);
//	}
//}

void UserInterface::checkMenuChoice()
{
	// ������� �������
	int key;

	do {

		this->keyBoard->waitForKey();

		key = this->keyBoard->getPressedKey();

	}	// ���� ������� ������� �� ������������ ������� ����
	while (this->func(key));
}

void UserInterface::checkArrowsChoice(bool &exitFlag, int BorderYCoord, int keyCode)
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

//void UserInterface::checkExit()
//{
//	
//}

//void UserInterface::doAlchemy()
//{
//	//printContinueGameMenu();
//
//	// !!! ������ ��, �.�. ���� ����� ��������� !!!
//
//	//cout << "������ ���������� ��������� ���� ��� ������� �����?" << endl
//	//	<< "1 - ���������� ����" << endl
//	//	<< "2 - ������� ����� ����" << endl;
//
//	//func = std::bind(&UserInterface::isContinueGameFalse, this, _1);
//
//	//checkMenuChoice();
//
//	// !!! ����� ��������
//	// ��� ��������
//
//
//
//
//
//	// !!! �������� !!!
//
//	// ���� ��� ������������ ������
//	if ("" == this->alchemist->getName())
//	{
//		// ��� ������������
//		string name;
//
//		cout << "������� ���� ���: ";
//
//		cin >> name;
//
//		this->alchemist->setName(name);
//	}
//
//
//
//	//string name = "������";
//
//	eraseScreenAfterTitle();
//
//	//this->alchemist->setName(name);
//
//	this->alchemist->print();
//
//	printActionMenu();
//
//}