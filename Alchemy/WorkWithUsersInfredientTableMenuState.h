#pragma once
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define MINIMUM_NUMBER_OF_INGREDIENTS		1		// Минимальное кол-во ингредиентов

// Состояние меню - работа с ингредиентами юзера
class WorkWithUsersInfredientTableMenuState : public WorkWithIngredientTableMenuState
{
public:

	// Конструктор по умолчанию
	WorkWithUsersInfredientTableMenuState();

	// Конструктор с параметром
	WorkWithUsersInfredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

protected:

	// Задать контент для печати
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

