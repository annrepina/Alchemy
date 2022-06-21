#pragma once
#include "MenuState.h"

class SellingPotionsMenuState : public MenuState
{
public:

	SellingPotionsMenuState();

	SellingPotionsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~SellingPotionsMenuState() override;

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
	map<int, function<MenuState* (SellingPotionsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (SellingPotionsMenuState&)> > listOfCreatingFunctions;

	//// Создать состояние - алхимическое меню
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// Создать состояние - меню инструкций
	//InstructionsMenuState* createInstructionsMenuState();
};

