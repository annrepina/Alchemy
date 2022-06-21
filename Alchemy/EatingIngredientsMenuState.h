#pragma once
#include "MenuState.h"

class EatingIngredientsMenuState : public MenuState
{
public:

	EatingIngredientsMenuState();

	EatingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);
	
	~EatingIngredientsMenuState() override;

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
	map<int, function<MenuState* (EatingIngredientsMenuState&)> > stateCreatingFunctions;

	// ��������� map �������, ������� ������� ������ � �� �����
	void fillStateCreatingFunctions();

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (EatingIngredientsMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

