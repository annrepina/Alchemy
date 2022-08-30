#pragma once
//#include "MenuState.h"
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"
//#include "MenuState.h"

class WorkWithUsersInfredientTableMenuState : public WorkWithIngredientTableMenuState/*, public MenuState*/
{
public:

	WorkWithUsersInfredientTableMenuState();

	WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

protected:

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

