#pragma once
#include "MenuState.h"

class SellingIngredientsMenuState : public MenuState
{
public:

	SellingIngredientsMenuState();

	SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingIngredientsMenuState() override;

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
	map<int, function<MenuState* (SellingIngredientsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (SellingIngredientsMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

