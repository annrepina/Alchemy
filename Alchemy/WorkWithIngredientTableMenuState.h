#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define INNER_MENU_ITEMS	2	// 2 внутренних пункта меню

class AlchemicalUserInterface;

class WorkWithIngredientTableMenuState : public MenuState
{
public:

	WorkWithIngredientTableMenuState();

	WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

	// Печать меню
	void printMenu() override;

protected:



private:

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void printMenuItems() override;

	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode) override;

	void chooseMenuItem() override;

	void setListOfInnerMenuItems();

	// Определить операцию сортировка или посиск
	int defineOperation();
};

