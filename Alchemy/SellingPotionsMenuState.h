#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define MINIMUM_NUMBER_OF_POTIONTS_FOR_SELLING		1	// минимально требуемое кол-во зелья для ПРОДАЖИ 

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

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void printMenu(string choiceIngredient, string choiceNumberOfIngredient);
};

