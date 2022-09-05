#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS						3		// 3 внутренних пункта меню

#define DEFAULT_NUMBER_OF_COLUMN				1		// Номер колонки по умолчанию при работе с таблицей
#define NUMBER_OF_SEARCHING_QUERIES				9		// Кол-во поисковых запросов для таблицы с ингредиентами

#define X_COORD_FOR_FILTER_ITEMS				20		// Координата для печати пунктов меню во время фильтрации
#define	GAP_BETWEEN_FILTER_AND_VALUE			5		// Простраство между фильтром и запросом

// Стринговые фильтры согласно их координатам по Y
#define FILTER_NAME_3								3		// Фильтр по имени
#define FILTER_EFFECT_6								6		// Фильтр по эффекту 1
#define FILTER_EFFECT_7								7		// Фильтр по эффекту 2

#define COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE	2		// Разница в кооординатах между двоеточием и значением для ффильтраци

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
	int numberOfColumnforSorting;

	// Порядок сортировки
	bool orderOfSorting;

	// Координата х для печати выбора для фильтрации
	int xCoordForFilterValue;

	IngredientsTablePrinter* ingredientTablePrinter;

	// Поисковые запросы
	vector<string> searchingQueries;

	// Добавляет поисковой запрос
	void addSearchingQuery(string query, int numberOfQuery);

#pragma region Сеттеры

	// Задать вектор поисковых запросов по умолчанию
	void setSearchingQueriesDefault();

	// Задать контент для печати
	virtual void setContent();

	// Задать список создающих стейты функций
	void setListOfCreatingFunctions() override;

	void setListOfInnerMenuItems();

	void setListOfColumnTitles();

#pragma endregion Сеттеры

	// Исходный контент таблицы - Весь
	vector<vector<string>> initialContent;

	// Контент после сортировки
	vector<vector<string>> contentAfterSortingAndResearch;

	// Пункты внутреннего меню
	map<int, string> innerMenuItems;

	vector<string> listOfInnerMenuItems;

	// Колонки для фильтрации
	map<int, string> columnForFiltration;

	vector<string> listOfColumnForFiltration;

	int longestColumnSize;

	virtual void printMenuItems(vector<string> listOfItems);

	virtual void printFilterItems(vector<string> listOfItems);

	//void chooseMenuItem() override;

	void chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting);

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

	// Запустить сортировку
	virtual void launchSorting();

	virtual void launchFilterMenu();

	virtual void filterData();

	// Расчитать самый длинный пункт фильтрации (название столбца)
	virtual int calculateLongestFIlteringItem();

	// Искомая колонка является стринговой или интовой в тбалице?
	virtual bool isStringColumn(int numberOfColumn);

	int calculateNumberOfColumnForFiltration();

private:

	// Задать список состояний
	void setListOfStates() override;

	// Map функций, которые создают стейты и их ключи - координаты пунктов меню
	map<int, function<MenuState* (WorkWithIngredientTableMenuState&)> > stateCreatingFunctions;

	// Вектор функций, которые создают стейты
	vector< function<MenuState* (WorkWithIngredientTableMenuState&)> > listOfCreatingFunctions;

	// Создать состояние - меню назад
	ReturnMenuState* createReturnMenuState();

	void checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items);
};

