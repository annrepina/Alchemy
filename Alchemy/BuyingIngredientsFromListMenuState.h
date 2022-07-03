#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define FIRST_PAGE						1		// ������ �������� �������
//#define INGREDIENTS_TABLE				0		// ������� ������������

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

	// �������� ��������� ���������
	MenuState* getNextState() override;

private:

	//// ������ ��� ������� � map
	//int index;

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

