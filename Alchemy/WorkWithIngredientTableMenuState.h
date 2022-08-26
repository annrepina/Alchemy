#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define INNER_MENU_ITEMS	2	// 2 ���������� ������ ����

class AlchemicalUserInterface;

class WorkWithIngredientTableMenuState : public MenuState
{
public:

	WorkWithIngredientTableMenuState();

	WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

	// ������ ����
	void printMenu() override;

protected:



private:

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	void printMenuItems() override;

	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode) override;

	void chooseMenuItem() override;

	void setListOfInnerMenuItems();

	// ���������� �������� ���������� ��� ������
	int defineOperation();
};

