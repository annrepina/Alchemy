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

	~MainMenuState() override;

	// ������ ����
	void printMenu() override;

	AlchemicalMenuState* createAlchemicalMenuState();

	InstructionsMenuState* createInstructionsMenuState();

	// Map �������, ������� ������� ������
	map<int, function<MenuState* (MainMenuState&)> > stateCreatingFunctions;

	void fillStateCreatingFunctions();

	vector< function<MenuState* (MainMenuState&)> > listOfCreatingFunctions;

	MenuState* getNextState() override;

	//void clear() override;
	 
protected:



private:

	void setListOfStates() override;

	void setListOfCreatingFunctions() override; 
};


