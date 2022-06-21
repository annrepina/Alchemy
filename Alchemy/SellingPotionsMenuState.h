#pragma once
#include "MenuState.h"

class SellingPotionsMenuState : public MenuState
{
public:

	SellingPotionsMenuState();

	SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingPotionsMenuState() override;

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
	map<int, function<MenuState* (SellingPotionsMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (SellingPotionsMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

