#pragma once
#include "MenuState.h"
#include "WorkWithIngredientTableMenuState.h"
#include "WorkWithPotionTableMenuState.h"
#include "WorkWithUsersInfredientTableMenuState.h"
#include "ServiceFunctions.h"

#define WORK_WITH_TABLES_MENU_ITEMS		4	// ���-�� ������� ���� ������ � ���������

// ��������� ���� - ������ � ���������
class WorkWithTablesMenuState : public MenuState
{
public:

	// ����������� �� ���������
	WorkWithTablesMenuState();

	// ����������� � ����������
	WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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

	// ������� ��������� - ���� �����s � �������� ������������
	WorkWithIngredientTableMenuState* createWorkWithIngredientTableMenuState();

	// ������� ��������� - ���� ������ � �������� ������������
	WorkWithPotionTableMenuState* createWorkWithPotionTableMenuState();

	// ������� ��������� - ���� ������ � �������� ������������ ������������
	WorkWithUsersInfredientTableMenuState* createWorkWithUsersInfredientTableMenuState();
};