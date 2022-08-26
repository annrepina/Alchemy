#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

class AlchemicalMenuState;

class WorkWithPotionTableMenuState : public MenuState
{
public:

	WorkWithPotionTableMenuState();

	WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

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
	map<int, function<MenuState* (WorkWithPotionTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithPotionTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};

