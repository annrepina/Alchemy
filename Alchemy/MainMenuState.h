#pragma once
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

	// ����������� �� ���������
	MainMenuState();

	// ����������� � �����������
	MainMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;

	void setListOfStates() override;
	 
protected:



private:
};


