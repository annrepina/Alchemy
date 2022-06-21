#pragma once
#include "MenuState.h"

class SellingIngredientsMenuState : public MenuState
{
public:

	SellingIngredientsMenuState();

	SellingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingIngredientsMenuState() override;

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
	map<int, function<MenuState* (SellingIngredientsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (SellingIngredientsMenuState&)> > listOfCreatingFunctions;

	//// Создать состояние - алхимическое меню
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// Создать состояние - меню инструкций
	//InstructionsMenuState* createInstructionsMenuState();
};

