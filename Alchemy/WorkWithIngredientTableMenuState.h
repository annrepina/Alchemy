#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS						3		// 3 внутренних пункта меню

#define DEFAULT_NUMBER_OF_COLUMN				1		// Номер колонки по умолчанию при работе с таблицей
#define NUMBER_OF_INGREDIENT_TABLE_COLUMNS		6		// Кол-во колонк в таблице с ингредиентами

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

	// Поисковые запросы
	vector<string> searchingQueries;

	// Задать вектор поисковых запросов по умолчанию
	void setSearchingQueriesDefault();

	// Задать контент для печати
	virtual void setContent();

	// Исходный контент таблицы - Весь
	vector<vector<string>> initialContent;

	// Контекент после печати и поиска
	vector<vector<string>> contentAfterSortingAndSearch;

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	void setListOfColumnTitles();

	// Пункты внутреннего меню
	map<int, string> innerMenuItems;

	// Колонки для фильтрации
	map<int, string> columnForFiltration;

	vector<string> listOfColumnTitles;

	vector<string> listOfInnerMenuItems;

	void printMenuItems(vector<string> listOfItems);

	//void chooseMenuItem() override;

	void chooseMenuItem(vector<string> listOfItems);

	// Выбрать колонку для фильтрации
	void chooseFilterColumn();

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

	virtual void filterData();

private:

	// Задать список состояний
	void setListOfStates() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int keyCode, vector<string> items);
};

