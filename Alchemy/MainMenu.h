#pragma once
#include "MenuState.h"

class MainMenu : public MenuState
{
public:

	// ����������� �� ���������
	MainMenu();

	// ����������� � �����������
	MainMenu(AlchemicalUserInterface* alchemicalUserInterface);

	// ������ ����
	void printMenu() override;
	 
protected:



private:
};


