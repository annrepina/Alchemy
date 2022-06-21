#pragma once
#include "MenuState.h"
#include "CreatingPotionsMenuState.h"

#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	7		// ���-�� ������� � ������������ ����

class AlchemicalMenuState : public MenuState
{
public:

	// ����������� �� ���������
	AlchemicalMenuState();

	AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~AlchemicalMenuState() override;

	// ������ ����
	void printMenu() override;

protected:

private:

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (AlchemicalMenuState&)> > stateCreatingFunctions;

	// ��������� map �������, ������� ������� ������ � �� �����
	void fillStateCreatingFunctions();

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (AlchemicalMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

