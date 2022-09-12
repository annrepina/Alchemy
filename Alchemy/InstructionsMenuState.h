#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define NUMBER_OF_INSTRUCIONS_MENU_ITEMS	1		// ���-�� ������� � ���� ����������

class MainMenuState;

// ��������� ���� - ����������
class InstructionsMenuState : public MenuState
{
public:

	// ����������� �� ���������
	InstructionsMenuState();

	// ����������� � ����������
	InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

private:

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (InstructionsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (InstructionsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};