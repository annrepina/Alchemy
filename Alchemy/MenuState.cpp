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
	//this->exitFlag = false;
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
	// ���������� Y
	//int yCoord = this->alchemicalUserInterface->getCurrentYCursorCoord();
	//int yCoord = this->currentYCursorCoordState;

	// ��������� ���� � ������������� �������
	//int border = yCoord + menu.size();
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

int MenuState::printChoiceIngredientId(int yCoord, int xCoord)
{
	// ��������� �� ���������� ��� ����� ������� id
	cout << goToXY(yCoord, xCoord);

	int ingredientId = alchemicalUserInterface->chooseId(AlchemicalUserInterface::TableCode::IngredientTable);

	return ingredientId;
}

void MenuState::chooseMenuItem()
{
	this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));

	//this->alchemicalUserInterface->setFunc(AlchemicalUserInterface::isArrowKeyFalse(1));
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
			this->alchemicalUserInterface->setExitFlag(true);
			//exitFlag = true;
		}
		break;
		}
	} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
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
				this->alchemicalUserInterface->setExitFlag(true);
			}
			break;
		}
	} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
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
		delete state;

		state = nullptr;
	}
}

bool MenuState::wasExit(int number)
{
	if (number == EXIT_INT)
	{
		this->alchemicalUserInterface->setState(this->getNextState());

		return true;
	}

	return false;
}

void MenuState::exitMenu()
{
	// ���������� ����
	this->alchemicalUserInterface->setExitFlag(false);

	this->alchemicalUserInterface->setState(this->getNextState());
}

