#pragma once
#include "MenuState.h"
#include "ReturnMenuState.h"
#include "IngredientsTablePrinter.h"

#define INNER_MENU_ITEMS							3		// 3 внутренних пункта меню

#define DEFAULT_NUMBER_OF_COLUMN					1		// Номер колонки по умолчанию при работе с таблицей
#define NUMBER_OF_SEARCHING_QUERIES					9		// Кол-во поисковых запросов для таблицы с ингредиентами

#define X_COORD_FOR_FILTER_ITEMS					20		// Координата для печати пунктов меню во время фильтрации
#define	GAP_BETWEEN_FILTER_AND_VALUE				5		// Простраство между фильтром и запросом

// Стринговые фильтры согласно их координатам по Y
#define FILTER_NAME_3								3		// Фильтр по имени
#define FILTER_EFFECT_6								6		// Фильтр по эффекту 1
#define FILTER_EFFECT_7								7		// Фильтр по эффекту 2

#define COORD_DIFFERENCE_BETWEEN_COLON_AND_VALUE	2		// Разница в кооординатах между двоеточием и значением для ффильтраци

class AlchemicalUserInterface;

// Состояние меню - работа с таблицей ингредиентов
class WorkWithIngredientTableMenuState : public MenuState
{
public:

	// Конструктор по умолчанию
	WorkWithIngredientTableMenuState();

	// Конструктор с параметром
	WorkWithIngredientTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	void printMenu() override;

protected:

	// Номер столбца, по которому сортируем
	int numberOfColumnforSorting;

	// Порядок сортировки
	bool orderOfSorting;

	// Координата х для печати выбора для фильтрации
	int xCoordForFilterValue;

	// Принтер ингредиентов
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

	// Задать список внутренних пунктов меню
	void setListOfInnerMenuItems();

	// Задать списо названий фильтров для столбцов
	virtual void setListOfColumnFilters();

	// задаем некоторые поля
	virtual void setFields();

#pragma endregion Сеттеры

	// Исходный контент таблицы - Весь
	vector<vector<string>> initialContent;

	// Контент после сортировки
	vector<vector<string>> contentAfterSortingAndResearch;

	// Пункты внутреннего меню с координатами по Y
	map<int, string> innerMenuItems;

	// Список пунктов внутреннего меню
	vector<string> listOfInnerMenuItems;

	// Колонки для фильтрации и координаты по Y
	map<int, string> columnForFiltration;

	// Список названий пунктов для фильтрации
	vector<string> listOfColumnFilters;

	// Длина самого длинного названия фильтра для столбца
	int longestFilterSize;

	// Печать пунктов меню
	virtual void printMenuItems(vector<string> listOfItems);

	// Печать пунктов фильтрации
	virtual void printFilterItems(vector<string> listOfItems);

	// Работать с таблицей
	virtual void workWithTable();

	// Выбрать пункт меню
	void chooseMenuItem(vector<string> listOfItems, int xCoordForItemsPrinting);

	// Получить следующее состояние
	MenuState* getNextState() override;

	// Определить операцию сортировка или посиск
	int defineOperation();

	// Коды операций
	enum class OperationCode
	{
		Sorting,
		Search
	};

	// Работать с таблицой - перегрузка
	virtual void workWithTable(OperationCode operationCode);

	// Запустить меню сортировки
	virtual void launchSortingMenu();

	// Запустить сортировку
	virtual void sortData();

	// Запустить меню фильтрации
	virtual void launchFilterMenu();

	// Фильтровать данные
	virtual void filterData();

	// Расчитать самый длинный пункт фильтрации (название столбца)
	virtual int calculateLongestFIlteringItem();

	// Искомая колонка является стринговой или интовой в тбалице?
	virtual bool isStringColumn(int numberOfColumn);

	// Рассчитать по какой колонке фильтрация
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

	// Проверить выбор вертикальных стрелочек на корректность
	void checkVerticalArrowsChoice(int borderYCoord, int xCoordForItemPrinting, int keyCode, vector<string> items);
};