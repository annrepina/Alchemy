#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"

#define FIRST_PAGE						1		// Первая страница таблицы

class BuyingIngredientsMenuState;

// Класс - состояние меню покупки ингредиентов из списка
class BuyingIngredientsFromListMenuState : public MenuState
{
public:

	BuyingIngredientsFromListMenuState();

	BuyingIngredientsFromListMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	/*~BuyingIngredientsFromListMenuState();*/

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
	map<int, function<MenuState* (BuyingIngredientsFromListMenuState&)> > stateCreatingFunctions;

	//// Заполнить map функций, которые создают стейты и их ключи
	//void fillStateCreatingFunctions();

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (BuyingIngredientsFromListMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	//// Создать состояние - меню инструкций
	//InstructionsMenuState* createInstructionsMenuState();
};

