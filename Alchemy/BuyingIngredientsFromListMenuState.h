#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define FIRST_PAGE						1		// Первая страница таблицы
//#define INGREDIENTS_TABLE				0		// Таблица ингредиентов

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

	// Получить следующее состояние
	MenuState* getNextState() override;

private:

	//// Индекс для функций в map
	//int index;

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

