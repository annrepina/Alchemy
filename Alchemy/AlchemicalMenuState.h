#pragma once
#include "MenuState.h"
#include "CreatingPotionsMenuState.h"
#include "BuyingIngredientsMenuState.h"
#include "SellingIngredientsMenuState.h"
#include "EatingIngredientsMenuState.h"
#include "SellingPotionsMenuState.h"
#include "WorkWithTablesMenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define EDITION

#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS		7	// ���-�� ������� � ������������ ����

class MainMenuState;

// ��������� ���� - ������������ ����
class AlchemicalMenuState : public MenuState
{
public:

	// ����������� �� ���������
	AlchemicalMenuState();

	// ����������� � ����������
	AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (AlchemicalMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (AlchemicalMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �������� �����
 	CreatingPotionsMenuState* createCreatingPotionsMenuState();

	// ������� ��������� - ���� ������� ������������
	BuyingIngredientsMenuState* createBuyingIngredientsMenuState();

	// ������� ��������� - ���� ������� ������������
	SellingIngredientsMenuState* createSellingIngredientsMenuState();

	// ������� ��������� - ���� �������� ������������
	EatingIngredientsMenuState* createEatingIngredientsMenuState();

	// ������� ��������� - ���� ������� �����
	SellingPotionsMenuState* createSellingPotionsMenuState();

	// ������� ��������� - ���� ������ � ���������
	WorkWithTablesMenuState* createWorkWithTablesMenuState();

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};

