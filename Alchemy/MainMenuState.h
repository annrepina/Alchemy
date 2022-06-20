#pragma once
#include "MenuState.h"
#include "AlchemicalMenuState.h"
#include "InstructionsMenuState.h"

// ���-��
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// ���-�� ������� � ������� ����

class MainMenuState : public MenuState
{
public:

	// ����������� �� ���������
	MainMenuState();

	// ����������� � �����������
	MainMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ����������
	~MainMenuState() override;

	// ������ ����
	void printMenu() override;

private:

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ������������ ����
	AlchemicalMenuState* createAlchemicalMenuState();

	// ������� ��������� - ���� ����������
	InstructionsMenuState* createInstructionsMenuState();

	// ��������� map �������, ������� ������� ������ � �� �����
	void fillStateCreatingFunctions();

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// 
	void setListOfStates() override;

	void setListOfCreatingFunctions() override; 
};


