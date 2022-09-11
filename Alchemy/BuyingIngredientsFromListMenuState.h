#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define FIRST_PAGE						1		// Первая страница таблицы

class BuyingIngredientsMenuState;

// Состояние меню - покупка ингредиентов из списка
class BuyingIngredientsFromListMenuState : public MenuState
{
public:

	BuyingIngredientsFromListMenuState();

	BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

	// Получить следующее состояние
	MenuState* getNextState() override;

private:

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (BuyingIngredientsFromListMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (BuyingIngredientsFromListMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();
};

