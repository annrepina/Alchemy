#pragma once
#include "MenuState.h"
#include "ServiceFunctions.h"
#include "BuyingIngredientsFromListMenuState.h"
#include "BuyNewIngredientsMenuState.h"

#define NUMBER_OF_BUYING_MENU_ITEMS		3		// Кол-во пунктов в меню покупки ингредиентов

class AlchemicalMenuState;

class BuyingIngredientsMenuState : public MenuState
{
public:

	BuyingIngredientsMenuState();

	BuyingIngredientsMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~BuyingIngredientsMenuState() override;

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

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (BuyingIngredientsMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню покупки зелий из списка
	BuyingIngredientsFromListMenuState* createBuyingIngredientsFromListMenuState();

	// Создать состояние - меню инструкций
	BuyNewIngredientsMenuState* createBuyNewIngredientsMenuState();

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

};

