#pragma once
#include "MenuState.h"

class ReturnMenuState : public MenuState
{
public:

	ReturnMenuState(MenuState* previousMenuState, AlchemicalUserInterface* alchemicalUserInterface);

	//~ReturnMenuState() override;

	// Печать меню
	void printMenu() override;

private:

	// Предыдущее меню 
	MenuState* previuosMenuState;

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;


};

