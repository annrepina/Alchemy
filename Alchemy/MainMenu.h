#pragma once
#include "MenuState.h"

class MainMenu : public MenuState
{
public:

	// Конструктор по умолчанию
	MainMenu();

	// Конструктор с параметрами
	MainMenu(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;
	 
protected:



private:
};


