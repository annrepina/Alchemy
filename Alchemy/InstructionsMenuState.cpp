#include "InstructionsMenuState.h"
#include "MainMenuState.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "����������� ����������� ��������";
	this->goToTitle = "������ ����������� ����������� ��������";
	this->numberOfStates = NUMBER_OF_INSTRUCIONS_MENU_ITEMS;
}

//InstructionsMenuState::~InstructionsMenuState()
//{ 
//	clear();
//}

void InstructionsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();

	fillMap<function<MenuState* (InstructionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);

	cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	cout << "������������ � ����������� � ���������";

	MenuState::printMenu();
}

MenuState* InstructionsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void InstructionsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void InstructionsMenuState::setListOfCreatingFunctions()
{
	// ���� ������ ������
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&InstructionsMenuState::createReturnMenuState);
	}
}

//void InstructionsMenuState::fillStateCreatingFunctions()
//{
//	// ��������� ���� � ������������� �������
//	int startKey = this->currentYCursorCoordState;
//
//	// ��������� ������������� ������
//	for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
//	{
//		stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
//	}
//}

ReturnMenuState* InstructionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
