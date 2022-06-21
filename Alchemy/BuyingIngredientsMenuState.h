#pragma once
#include "MenuState.h"

class BuyingIngredientsMenuState : public MenuState
{
public:

	BuyingIngredientsMenuState();

	BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	~BuyingIngredientsMenuState() override;

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
	map<int, function<MenuState* (BuyingIngredientsMenuState&)> > stateCreatingFunctions;

	// Заполнить map функций, которые создают стейты и их ключи
	void fillStateCreatingFunctions();

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (BuyingIngredientsMenuState&)> > listOfCreatingFunctions;

	//// Создать состояние - алхимическое меню
	//AlchemicalMenuState* createAlchemicalMenuState();

	//// Создать состояние - меню инструкций
	//InstructionsMenuState* createInstructionsMenuState();

};

