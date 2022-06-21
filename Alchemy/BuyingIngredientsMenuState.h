#pragma once
#include "MenuState.h"

class BuyingIngredientsMenuState : public MenuState
{
public:

	BuyingIngredientsMenuState();

	BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~BuyingIngredientsMenuState() override;

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

	// ��������� map �������, ������� ������� ������ � �� �����
	void fillStateCreatingFunctions();

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (BuyingIngredientsMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();

};

