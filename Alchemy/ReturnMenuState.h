#pragma once
#include "MenuState.h"

// Состояние меню - назад
class ReturnMenuState : public MenuState
{
public:

	// Конструктор с параметром
	ReturnMenuState(MenuState* previousMenuState, AlchemicalUserInterface* alchemicalUserInterface);

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