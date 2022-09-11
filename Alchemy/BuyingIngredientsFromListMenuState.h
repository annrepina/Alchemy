#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define FIRST_PAGE						1		// ������ �������� �������

class BuyingIngredientsMenuState;

// ��������� ���� - ������� ������������ �� ������
class BuyingIngredientsFromListMenuState : public MenuState
{
public:

	BuyingIngredientsFromListMenuState();

	BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

	// �������� ��������� ���������
	MenuState* getNextState() override;

private:

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (BuyingIngredientsFromListMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (BuyingIngredientsFromListMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};

