#pragma once
#include "MenuState.h"
#include "WorkWithIngredientTableMenuState.h"
#include "WorkWithPotionTableMenuState.h"
#include "ServiceFunctions.h"

#define WORK_WITH_TABLES_MENU_ITEMS		3	// ���-�� ������� ���� ������ � ���������

class WorkWithTablesMenuState : public MenuState
{
public:

	WorkWithTablesMenuState();

	WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (WorkWithTablesMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithTablesMenuState&)> > listOfCreatingFunctions;

		// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	WorkWithIngredientTableMenuState* createWorkWithIngredientTableMenuState();

	WorkWithPotionTableMenuState* createWorkWithPotionTableMenuState();
};

