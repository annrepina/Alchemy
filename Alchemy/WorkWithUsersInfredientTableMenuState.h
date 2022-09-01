#pragma once
//#include "MenuState.h"
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"
//#include "MenuState.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS		1		// Минимальное кол-во ингредиентов

class WorkWithUsersInfredientTableMenuState : public WorkWithIngredientTableMenuState/*, public MenuState*/
{
public:

	WorkWithUsersInfredientTableMenuState();

	WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

protected:

	void setContent() override;

private:

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithUsersInfredientTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithUsersInfredientTableMenuState&)> > listOfCreatingFunctions;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	// Получить следующее состояние
	MenuState* getNextState() override;
};

