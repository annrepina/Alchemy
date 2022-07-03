#pragma once
#include "MenuState.h"
#include "ServiceFunctions.h"
#include "IngredientBuilder.h"

class BuyNewIngredientsMenuState : public MenuState
{
public:

	BuyNewIngredientsMenuState();

	BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (BuyNewIngredientsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (BuyNewIngredientsMenuState&)> > listOfCreatingFunctions;

};

