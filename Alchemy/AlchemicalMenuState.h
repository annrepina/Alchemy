#pragma once
#include "MenuState.h"
#include "CreatingPotionsMenuState.h"
#include "BuyingIngredientsMenuState.h"
#include "SellingIngredientsMenuState.h"
#include "EatingIngredientsMenuState.h"
#include "SellingPotionsMenuState.h"
#include "WorkWithTablesMenuState.h"
#include "ReturnMenuState.h"
#include "ServiceFunctions.h"

#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	7		// Кол-во пунктов в алхимическом меню

class MainMenuState;

class AlchemicalMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	AlchemicalMenuState();

	AlchemicalMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~AlchemicalMenuState() override;

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
	map<int, function<MenuState* (AlchemicalMenuState&)> > stateCreatingFunctions;

	//// Заполнить map функций, которые создают стейты и их ключи
	//void fillStateCreatingFunctions();

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (AlchemicalMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню создания зелий
 	CreatingPotionsMenuState* createCreatingPotionsMenuState();

	// Создать состояние - меню покупки ингредиентов
	BuyingIngredientsMenuState* createBuyingIngredientsMenuState();

	// Создать состояние - меню продажи ингредиентов
	SellingIngredientsMenuState* createSellingIngredientsMenuState();

	// Создать состояние - меню поедания ингредиентов
	EatingIngredientsMenuState* createEatingIngredientsMenuState();

	// Создать состояние - меню продажи зелий
	SellingPotionsMenuState* createSellingPotionsMenuState();

	// Создать состояние - меню работы с таблицами
	WorkWithTablesMenuState* createWorkWithTablesMenuState();

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

};

