#pragma once
#include "MenuState.h"
#include "WorkWithIngredientTableMenuState.h"
#include "WorkWithPotionTableMenuState.h"
#include "ServiceFunctions.h"

#define WORK_WITH_TABLES_MENU_ITEMS		3	// Кол-во пунктов меню работы с таблицами

class WorkWithTablesMenuState : public MenuState
{
public:

	WorkWithTablesMenuState();

	WorkWithTablesMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

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
	map<int, function<MenuState* (WorkWithTablesMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithTablesMenuState&)> > listOfCreatingFunctions;

		// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	WorkWithIngredientTableMenuState* createWorkWithIngredientTableMenuState();

	WorkWithPotionTableMenuState* createWorkWithPotionTableMenuState();
};

