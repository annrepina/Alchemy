#pragma once
#include "MenuState.h"

class CreatingPotionsMenuState : public MenuState
{
public:

	// ����������� �� ���������
	CreatingPotionsMenuState();

	// ����������� � �����������
	CreatingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ����������
	~CreatingPotionsMenuState() override;

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
	map<int, function<MenuState* (CreatingPotionsMenuState&)> > stateCreatingFunctions;

	// ��������� map �������, ������� ������� ������ � �� �����
	void fillStateCreatingFunctions();

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (CreatingPotionsMenuState&)> > listOfCreatingFunctions;

	//// ������� ��������� - ������������ ����
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// ������� ��������� - ���� ����������
	//InstructionsMenuState* createInstructionsMenuState();
};

