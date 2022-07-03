#pragma once
#include "MenuState.h"
#include "ServiceFunctions.h"
#include "IngredientBuilder.h"

class BuyNewIngredientsMenuState : public MenuState
{
public:

	BuyNewIngredientsMenuState();

	BuyNewIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

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
	map<int, function<MenuState* (BuyNewIngredientsMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (BuyNewIngredientsMenuState&)> > listOfCreatingFunctions;

};

