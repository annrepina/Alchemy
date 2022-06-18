#pragma once
#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	MainMenuState();

	// Конструктор с параметрами
	MainMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

	void setListOfStates() override;
	 
protected:



private:
};


