#include "MenuState.h"
#include "AlchemicalUserInterface.h"

int MenuState::currentYCursorCoordState = MAIN_MENU_Y_COORD;

int MenuState::currentXCursorCoordState = STANDARD_CURSOR_X_COORD;

MenuState::MenuState()
{
	this->title = "";
	this->goToTitle = "";
	this->alchemicalUserInterface = nullptr;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->numberOfStates = 0;
}

MenuState::MenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState()
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

MenuState::MenuState(MenuState const& copyMenuState)
{
	this->alchemicalUserInterface = copyMenuState.alchemicalUserInterface;
	this->boundaryYCoord = copyMenuState.boundaryYCoord;
	this->goToTitle = copyMenuState.goToTitle;
	this->numberOfStates = copyMenuState.numberOfStates;
	this->title = copyMenuState.title;
}

MenuState& MenuState::operator=(MenuState const& right)
{
	if (right.alchemicalUserInterface != nullptr)
	{
		this->alchemicalUserInterface = right.alchemicalUserInterface;
		this->boundaryYCoord = right.boundaryYCoord;
		this->goToTitle = right.goToTitle;
		this->numberOfStates = right.numberOfStates;
		this->title = right.title;
	}

	return *this;
}

MenuState::~MenuState()
{
	clear();
}

void MenuState::setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
{
	this->alchemicalUserInterface = alchemicalUserInterface;
}

void MenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	this->setListOfStates();

	fillMap<MenuState*>(menuStates, listOfStates, this->currentYCursorCoordState, this->numberOfStates);

	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	chooseMenuItem();

	this->alchemicalUserInterface->setState(this->getNextState());
}

void MenuState::printMenuTitle()
{
	this->currentXCursorCoordState = calculateXCoordInMiddle(title);
	
	cout << goToXY(this->currentYCursorCoordState - TWO_LINES, this->currentXCursorCoordState);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}

void MenuState::printMenuItems() 
{
	// ��������� ���� � ������������� �������
	int border = this->boundaryYCoord + this->menuStates.size();

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

int MenuState::printChoiceId(int yCoord, int xCoord, int tableCode)
{
	// ��������� �� ���������� ��� ����� ������� id
	cout << goToXY(yCoord, xCoord);

	int id = alchemicalUserInterface->chooseId((AlchemicalUserInterface::TableCode)tableCode);

	return id;
}

int MenuState::printChoiceNumber(int yCoord, string choice)
{
	int number = alchemicalUserInterface->chooseNumber(choice, yCoord);

	return number;
}

void MenuState::chooseMenuItem()
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	// ���� ��� ������ �� �����, �� �� ����� �� ���������
	bool innerExitFlag = false;

	do
	{
		// ��������� ������� ������
		this->alchemicalUserInterface->checkMenuChoice();

		switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
		{
			case VK_UP:
			{
				this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);
			}
			break;

			case VK_DOWN:
			{
				// ��������� ���������
				this->checkVerticalArrowsChoice(this->boundaryYCoord + menuStates.size() - 1, VK_DOWN);
			}
			break;

			case VK_RETURN:
			{
				// ����� �� �����
				innerExitFlag = true;
			}
			break;

			case VK_ESCAPE:
			{
				this->alchemicalUserInterface->setWasExit(true);
				//exitFlag = true;
			}
			break;
		}
	} while (false == this->alchemicalUserInterface->getWasExit() && false == innerExitFlag);
}

void MenuState::chooseContinueOrGoBack()
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isEnterEscKeyFalse, this->alchemicalUserInterface, _1));

	// ���� ��� ������ �� �����, �� �� ����� �� ���������
	bool innerExitFlag = false;

	do
	{
		// ��������� ������� ������
		this->alchemicalUserInterface->checkMenuChoice();

		//switch (this->keyBoard->getPressedKey())
		switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
		{
			case VK_RETURN:
			{
				// ����� �� �����
				innerExitFlag = true;
			}
			break;

			case VK_ESCAPE:
			{
				this->alchemicalUserInterface->setWasExit(true);
			}
			break;
		}
	} while (false == this->alchemicalUserInterface->getWasExit() && false == innerExitFlag);
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
			cout << menuStates[currentYCursorCoordState]->goToTitle;

			// ����������� ����������
			++this->currentYCursorCoordState;
		}
		// ���� ������ �����
		else
			// ��������� ����������
			--this->currentYCursorCoordState;

		// ��������� �� �����������
		cout << goToXY(this->currentYCursorCoordState, 0);

		printMenuItems();

		// ������������ � ����������
		cout << goToXY(currentYCursorCoordState, 0);
	}
}

void MenuState::clear()
{
	for (auto state : this->listOfStates)
	{
		if (nullptr != state)
		{
			delete state;
			state = nullptr;
		}
	}
}

void MenuState::goBack()
{
	// ���������� ����
	this->alchemicalUserInterface->setWasExit(false);

	this->alchemicalUserInterface->setState(this->getNextState());
}