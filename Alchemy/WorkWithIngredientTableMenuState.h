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

	// Номер столбца, по которому сортируем
	int numberOfColumn;

	// Порядок сортировки
	bool orderOfSorting;

	IngredientsTablePrinter* ingredientTablePrinter;

	// Задать контент для печати
	virtual void setContent();

	// Исходный контент таблицы - Весь
	vector<vector<string>> initialContent;

	// Контекент после печати и поиска
	vector<vector<string>> contentAfterSortingAndSearch;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	void printMenuItems() override;

	void chooseMenuItem() override;

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Определить операцию сортировка или посиск
	int defineOperation();

	enum class OperationCode
	{
		Sorting,
		Search
	};

	virtual void workWithTable(OperationCode operationCode);

	virtual void sortData();

private:

	// Задать список состояний
	void setListOfStates() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode) override;
};

