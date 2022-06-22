#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define FIRST_PAGE						1		// ������ �������� �������

class BuyingIngredientsMenuState;

// ����� - ��������� ���� ������� ������������ �� ������
class BuyingIngredientsFromListMenuState : public MenuState
{
public:

	BuyingIngredientsFromListMenuState();

	BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	/*~BuyingIngredientsFromListMenuState();*/

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
	map<int, function<MenuState* (BuyingIngredientsFromListMenuState&)> > stateCreatingFunctions;

	//// ��������� map �������, ������� ������� ������ � �� �����
	//void fillStateCreatingFunctions();

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (BuyingIngredientsFromListMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

