#include "MenuState.h"
#include "AlchemicalUserInterface.h"

int MenuState::currentYCursorCoordState = MAIN_MENU_Y_COORD;

int MenuState::currentXCursorCoordState = 0;

MenuState::MenuState()
{
	this->title = "";
	this->goToTitle = "";
	this->alchemicalUserInterface = nullptr;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->exitFlag = false; 
}

MenuState::MenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState()
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

MenuState::~MenuState()
{
}

void MenuState::setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

void MenuState::printMenu()
{
	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(/*this->alchemicalUserInterface->getCurrentYCursorCoord()*/this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	chooseMenuItem();

	this->alchemicalUserInterface->setState(this->menuStates[this->currentYCursorCoordState]);
}

void MenuState::printMenuTitle()
{
	//eraseScreenAfterAlchemist();

	//this->alchemicalUserInterface->setCurrentYCursorCoord(calculateXCoordInMiddle(title));

	this->currentXCursorCoordState = calculateXCoordInMiddle(title);

	//this->alchemicalUserInterface->currentXCursorCoord = calculateXCoordInMiddle(title);

	//this->currentXCursorCoord = calculateXCoordInMiddle(title);

	/*cout << goToXY(this->alchemicalUserInterface->getCurrentYCursorCoord() - TWO_LINES, this->alchemicalUserInterface->getCurrentXCursorCoord());*/

	cout << goToXY(this->currentYCursorCoordState - TWO_LINES, this->currentXCursorCoordState);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}

void MenuState::printMenuItems() 
{
	// ���������� Y
	//int yCoord = this->alchemicalUserInterface->getCurrentYCursorCoord();
	//int yCoord = this->currentYCursorCoordState;

	// ��������� ���� � ������������� �������
	//int border = yCoord + menu.size();
	int border = this->currentYCursorCoordState + this->menuStates.size();

	// �������� ������������� ������
	for (int i = this->currentYCursorCoordState; i < border; ++i)
	{
		if (i == this->currentYCursorCoordState)
		{
			printTextWithBackground(this->menuStates[i]->goToTitle, R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
			cout << endl;
		}

		else
			// �������� ����� ����
			cout << menuStates[i]->goToTitle << endl;
	}
}

void MenuState::chooseMenuItem()
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	//this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	//// ���� ��� ����������� � ���������� ����, �� �� ����� �� ���������
	//bool innerExitFlag = false;

	// ���� ��� ������ �� �����, �� �� ����� �� ���������
	bool innerExitFlag = false;

	do
	{
		// ��������� ������� ������
		this->alchemicalUserInterface->checkMenuChoice();

		//checkMenuChoice();

		//switch (this->keyBoard->getPressedKey())
		switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
		{
		case VK_UP:
		{
			// ��������� ���������
			/*this->alchemicalUserInterface->checkVerticalArrowsChoice(this->alchemicalUserInterface->getBoundaryYCoord(), VK_UP, menu);*/
			this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);

			//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
		}
		break;

		case VK_DOWN:
		{
			// ��������� ���������
			this->checkVerticalArrowsChoice(this->boundaryYCoord + menuStates.size() - 1, VK_DOWN);

			//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
		}
		break;

		case VK_RETURN:
		{
			// ������� ����� ������ ����
			//makeChoice(innerExitFlag);// !! ������������� ��������

			// ����� �� �����
			innerExitFlag = true;
		}
		break;

		case VK_ESCAPE:
		{
			exitFlag = true;
		}
		break;
		}
	} while (false == exitFlag && false == innerExitFlag);
}

void MenuState::checkVerticalArrowsChoice(int borderYCoord, int keyCode)
{
	// ���� ��������� ���������� �� ����� �������
	if (borderYCoord != this->currentYCursorCoordState)
	{
		// ���� ������ ����
		if (VK_DOWN == keyCode)
		{
			// �������� ����� ���� ��� ���������
			cout << menuStates[currentYCursorCoordState];

			// ����������� ����������
			++this->currentYCursorCoordState;
		}
		// ���� ������ �����
		else
			// ��������� ����������
			--this->currentYCursorCoordState;

		// ��������� �� �����������
		cout << goToXY(this->currentYCursorCoordState, 0);

		printMenu();

		// ������������ � ����������
		cout << goToXY(currentYCursorCoordState, 0);
	}
}