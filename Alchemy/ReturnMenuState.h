#pragma once
#include "MenuState.h"

class ReturnMenuState : public MenuState
{
public:

	ReturnMenuState(MenuState* previousMenuState, AlchemicalUserInterface* alchemicalUserInterface);

	//~ReturnMenuState() override;

	// ������ ����
	void printMenu() override;

private:

	// ���������� ���� 
	MenuState* previuosMenuState;

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;


};

