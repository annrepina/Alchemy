#include "InstructionsMenuState.h"
#include "MainMenuState.h"
#include "AlchemicalUserInterface.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "����������� ����������� ��������";
	this->goToTitle = "������ ����������� ����������� ��������";
	this->numberOfStates = NUMBER_OF_INSTRUCIONS_MENU_ITEMS;
}
void InstructionsMenuState::printMenu()
{
	// ���������� ���������� ������ ��� ������ � ����� ������
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();
	this->setListOfStates();

	fillMap<function<MenuState* (InstructionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);
	fillMap<MenuState*>(menuStates, listOfStates, this->currentYCursorCoordState, this->numberOfStates);

	//cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	printMenuTitle();

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	cout << "������������ � ����������� � ���������:\n"
		<< "1. ��� �������� �� ���� ����������� ��������� ����� � ����, ��� ������������� ������ ������� ENTER.\n"
		<< "2. ��� ������ �� ��������� ������� ESC.\n"
		<< "3. ��� ������� ������������ � ������� �� ������ ���������� ������� � ������� ������ ������-�����. ��� ������������� ������ �������� ������� Enter.\n"
		<< "��� ������ �� ���� ������� ������� ESC �� ����� �������� ������� �������.��� ������� ����������� ������� ����� � ���������� �����������"
		<< "����� ������������� ������� ENTER.\n"
		<< "������� �� ������ ��������, ����� ������ ������� ��� ������� ������������, ����� �������� ��������� ����������� ��� �����, ����� ��������� ������.\n"
		<< "4. ��� ������� ������ ����������� ������� �������� �����������, ����� ��� ����������, ����� ������������� ������� ENTER.\n"
		<< "��� ������ �� ���� ������� ������ ����������� ������� ESC.\n"
		<< "������� �� ������ ��������, ����� ������ ������� ��� ������� ������������, ����� �������� ��������� ����������� ��� �����, ����� ��������� ������.\n"
		<< "5. �� ����� �������� ����� �� ������ ���������� ������� � ������� ������ ������-�����. ��� ������������� ������ �������� ������� Enter\n"
		<< "��� ������ �� ���� ������� ������� ESC �� ����� �������� ������� �������\n"
		<< "��� �������� ����� ������� ����� 1�� � 2�� ����� � ����� �������� ���������� �����, ������� ������ �������, ����� ������������� ������� ENTER\n"
		<< "������� ����� ������ �� �����, ������� ���� � ��� � ���������.������� �� �� �����������, ��� ������ ���� �� ������ ���������� ��������� �����\n"
		<< "���� � ����� ������� �� �������, ��� ����� �������, �� �������� � �������� � ��������� ������� �����, �� � ��������� ����� ����� �� ����������,\n"
		<< "���� ������� � ������������ �� ���������\n"
		<< "��� ����, ����� ������� ������� � ������������ �� ������ �� ������!����� � ������������ �� ����������, �� ��� ������ ������� ������ �����!\n"
		<< "6. �� ����� �������� ����������� �� ������ ������ ��� ���������� ������. �� ����� �����������, ������� ������� ��� �������.\n"
		<< "�� ������ ���������� ������� ������������ � ������� ������ ������ - �����.��� ������������� ������ �������� ������� Enter\n"
		<< "��� ������ �� ���� ������� ������� ESC �� ����� �������� ������� �������.\n"
		<< "7. ��� ����, ����� �������������, �� ������ ������� ����������� ��� �����. �� ������ ���������� ������� � ������� ������ ������-�����.\n"
		<< "��� ������������� ������ �������� ������� Enter. ��� ������ �� ���� ������� ������� ESC �� ����� �������� ������� �������.\n"
		<< "��� ����, ����� ������� ����� ��� ����������, ������� �����, � ����� ����������.\n"
		<< "������� ������ ������ ��� ������������ � �����, ������� ���� � ��� � ���������\n"
		<< "��� ������������� ������ ������� Enter.����� ������� � ��� ���������� ������\n"
		<< "8. �� ����� ������ ���������� � ����� ����������, ��� ����� �������� � ��� ������ ��������: ���������� � ������� �������������, ������ �������������\n"
		<< "��� �������. �� ������ ����������� ���������� � ����� �� �������. ��� ������ ���� ����� ������ ������/����, � ����� ENTER ��� ������������� ������.\n"
		<< "����� ������� �� ������ ��������� ������� � ������� ������ ������/�����, � ����� ����������� ����� � ������� ENTER ��� ����� � ���������� ���� ����� ESC\n"
		<< "��� ���������� ����������� ��������� ����� / ���� ����� ����������� �� �������� ��� �����������, \n"
		<< "� ����� �������� ������ / ����� ��� ������ �������, �� �������� ������ �����������. \n"
		<< "������ ��� ����� ������ ���������� ���������� �� ������ ����� ���������� �������, ����� ���������� �� ���������.\n"
		<< "������������� ����� ��������, ����� �������� � ����������� ������ ���� ����� ESC ��� �������� � ����� ���� ������ ����.\n"
		<< "��� ������ �������� ������� ���������� �������� ����� / ����, ����� ���������� ����� ������� ENTER.����� ������� �������� ��������.\n"
		<< "�� ������� �������� �������� ���������. �� ����� ������ �� ���������, ����� ����������� ����� � �������� � ������� ������!\n"
		<< "����� �������, ���������� �������!";

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	chooseMenuItem();

	this->alchemicalUserInterface->setState(this->getNextState());
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

ReturnMenuState* InstructionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
