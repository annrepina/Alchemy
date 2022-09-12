#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define NUMBER_OF_INSTRUCIONS_MENU_ITEMS	1		// Кол-во пунктов в меню инструкций

class MainMenuState;

// Состояние меню - инструкции
class InstructionsMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	InstructionsMenuState();

	// Конструктор с параметром
	InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

private:

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (InstructionsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (InstructionsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();
};