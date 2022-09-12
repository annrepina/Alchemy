#pragma once
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS		1		// ����������� ���-�� ������������

// ��������� ���� - ������ � ������������� �����
class WorkWithUsersInfredientTableMenuState : public WorkWithIngredientTableMenuState
{
public:

	// ����������� �� ���������
	WorkWithUsersInfredientTableMenuState();

	// ����������� � ����������
	WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

protected:

	// ������ ������� ��� ������
	void setContent() override;

private:

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithUsersInfredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithUsersInfredientTableMenuState&)> > listOfCreatingFunctions;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	// �������� ��������� ���������
	MenuState* getNextState() override;
};

