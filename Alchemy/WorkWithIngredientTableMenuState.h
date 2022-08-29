#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS				3		// 3 внутренних пункта меню

#define DEFAULT_NUMBER_OF_COLUMN		1		// Номер колонки по умолчанию при работе с таблицей

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

	enum class OperationCode
	{
		Sorting,
		Search
	};

	// Номер столбца, по которому сортируем
	int numberOfColumn;

	// Порядок сортировки
	bool orderOfSorting;

	// Исходный контент таблицы - Весь
	vector<vector<string>> initialContent;

	// Контекент после печати и поиска
	vector<vector<string>> contentAfterSortingAndSearch;

	IngredientsTablePrinter* ingredientTablePrinter;

	// Получить следующее состояние

	MenuState* getNextState() override;

	// Задать список состояний
	void setListOfStates() override;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	// Задать контент для печати
	void setContent();

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

	void workWithTable(OperationCode operationCode);
};

