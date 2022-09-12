#pragma once
#include "MenuState.h"
#include "ServiceFunctions.h"
#include "BuyingIngredientsFromListMenuState.h"
#include "BuyNewIngredientsMenuState.h"

#define NUMBER_OF_BUYING_MENU_ITEMS		3		// ���-�� ������� � ���� ������� ������������

class AlchemicalMenuState;

// ��������� ���� - ������� ������������
class BuyingIngredientsMenuState : public MenuState
{
public:

	// ����������� �� ���������
	BuyingIngredientsMenuState();

	// ����������� � ����������
	BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (BuyingIngredientsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (BuyingIngredientsMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� ������� ����� �� ������
	BuyingIngredientsFromListMenuState* createBuyingIngredientsFromListMenuState();

	// ������� ��������� - ���� ������� ����� �����
	BuyNewIngredientsMenuState* createBuyNewIngredientsMenuState();

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};

