#pragma once
#include "UserInterface.h"
#include "AlchemyLogicBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"
#include "IObserver.h"
#include "PotionTablePrinter.h"
#include "AlchemyLogicWriter.h"
#include "AlchemyLogicReader.h"

// Координаты
#define TITLE_Y_COORD					1			// Координаты Y курсора для печати названия программы
#define EXIT_Y_COORD					2			// Координата Y кнопки выхода
#define Y_COORD_AFTER_ALCHEMIST			8			// Координата Y после печати алхимика
#define MAIN_MENU_Y_COORD				10			// Координата Y меню действий
#define PAGE_Y_COORD					44			// Координата Y меню страниц таблицы - УВЕЛИЧИЛА НА 6

// Значения по умолчанию
#define FIRST_PAGE						1			// Первая страница таблицы
#define DEFAULT_NUMBER_OF_COLUMN		1			// Номер колонки по умолчанию при работе с таблицей
#define MAX_INT							2147483647	// Самое большое число int 
#define TWO_LINES						2			// Две строчки

// Интерфейс программы - Зельеварение
class AlchemicalUserInterface : public UserInterface
{
public:

	// Конструктор по умолчанию
	AlchemicalUserInterface();

	// Запуск главного цикла программы
	void launchProgram() override;

#pragma region ГЕТТЕРЫ

	// Получить граничную координату Y для проверки нажатия стрелочек
	int getBoundaryYCoord();

	// Узнать был ли выход
	bool getWasExit();

	// Получить логику програмы зельеварения
	AlchemyLogic* getAlchemyLogic();

	// Получить принтер таблицы ингредиентов
	IngredientsTablePrinter* getIngredientsTablePrinter();

	// Получить принтер таблицы зелий
	PotionTablePrinter* getPotionTablePrinter();

#pragma endregion ГЕТТЕРЫ

#pragma region CЕТТЕРЫ

	// Установить состояние
	void setState(MenuState* state);

	// установить значение для булевой "был выход?"
	void setWasExit(bool exit);

	// Задать таблицы
	void setTables();

#pragma endregion CЕТТЕРЫ

	// Код таблицы
	enum class TableCode
	{
		IngredientTable,
		PotionTable
	};

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печать страниц таблиц в цикле
	void printTablePagesInLoop(TableCode code, int& page);

	// Печать страниц таблиц в цикле во время сортировки
	void printTablePagesInLoopWhileSorting(vector<vector<string>> content, TableCode code, int& page, int numberOfColumn, bool orderOfSorting);

	// Печать таблицы только с теми элементами, которые существуют у юзера
	void printTableWithAvailableToUserElements(TableCode code, int& page);

	// Печать таблицы первой страницы таблицы (только то, что есть у юзера)
	void printFirstTablePage(TableCode code);

	// Печать логику алхимии
	void printAlchemyLogic();

#pragma endregion МЕТОДЫ ПЕЧАТИ

#pragma region МЕТОДЫ ВЫБОРА

	// Выбрать Id из таблицы
	int chooseId(TableCode code);

	// Вбрать кол-во ингредиента или зелья
	int chooseNumber(string strChoice, int yCoord);

	// Сделать выход из меню
	void chooseExit();

	// Выбрать столбец и порядок сортировки
	void chooseColumnAndOrderOfSorting(int& numberOfColum, bool& orderOfSorting, TableCode code);

#pragma endregion МЕТОДЫ ВЫБОРА

	// Расчитать данные по таблицам
	void calculateTablesData();

	// Заполни контент таблиц
	void fillInTablesContent();

	// Назначить подписчиков
	void addSubscribers();

private:

	// Программа - алхимия
	AlchemyLogic* alchemyLogic;

	// Строитель для алхимической программы
	AlchemyLogicBuilder* alchemyLogicBuilder;

	// Райдер для логики алхимии
	AlchemyLogicWriter* alchemyLogicWriter;

	// Ридер для логики алхимии
	AlchemyLogicReader* alchemyLogicReader;

	// Принтер для печати таблицы ингредиентов
	IngredientsTablePrinter* ingredientsTableprinter;

	// Принтер печати таблицы зелий
	PotionTablePrinter* potionTablePrinter;

	// Состояние меню
	MenuState* state;

	// был выход из главного цикла?
	bool wasExit;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

	// Путь для записи
	string pathForWriting;

	// Настроить программу Алхимии
	void setAlchemyLogic();

	// Записать в файл логику программы зельеварения
	void writeAlchemyLogic();

	// Стирает с консоли все после печати алхимика
	void eraseScreenAfterAlchemist();

#pragma region НАЗВАНИЕ ЗАГОЛОВКОВ

	// Название главного меню
	string mainMenuTitle;

	// Название инструкции
	string instructionsMenuTitle;

	// Название меню алхимии
	string alchemicalMenuTitle;

	// Название меню покупки ингредиентов
	string buyingIngredientsMenuTitle;

	// Название меню ошибки во время покупки ингредиентов
	string buingFaultMenuTitle;

#pragma endregion НАЗВАНИЕ ЗАГОЛОВКОВ

#pragma region Выбор

	// Выбрать страницу таблицы
	void choosePage(int page, TableCode code);

	// Выбрать страницу во время сортировки
	void choosePageWhileSorting(vector<vector<string>> content, int page, TableCode code, int numberOfColumn, bool orderOfSorting);

	// Выбрать страницу таблицы среди доступных элементов
	void choosePageFromAvailableContent(int page, TableCode code);

#pragma endregion ВЫБОР

#pragma region ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

	// Проверить горизонтальные стрелки в случае с выбором страницы в таблицы
	bool checkHorizontalArrowChoice(int& page, TableCode code, int keyCode);

	// Проверить горизонтальные стрелки в случае с выбором страницы в таблицы
	bool checkHorizontalArrowChoice(int contentSize, int& page, TableCode code, int keyCode);

	// Проверить горизонтальные стрелки в случае с выбором столбца во время сортировки
	bool checkHorizontalArrowChoice(int& numberOfColums, int keyCode, TableCode code);

	// Проверить вертикальные стрелочки в случае выбора порядка сортировки
	bool checkVerticalArrowChoice(bool& orderOfSorting, int keyCode, TableCode code);

#pragma endregion ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	void printTitle() override;

	// Печатает "кнопку" выхода ESC
	void printExitButton() override;

	// Печать главного меню в цикле
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	// Печать прощания
	void printBye() override;

	// Печать инфы про алхимика
	void printAlchemist();

	// Печать названия Меню
	void printMenuTitle(string title);

	// Печать меню выбора страницы
	void printPageMenu(int page);

#pragma endregion МЕТОДЫ ПЕЧАТИ

#pragma region ПРЕДИКАТЫ

	// Неправилный выбор страницы
	bool isPageChoiceFalse(int key);

	// Неправильный выбор столбца или направления сортировки
	bool isColumnAndOrderChoiceFalse(int key);

	// Файл для печати пустой?
	bool isFileForReadingEmpty();

#pragma endregion ПРЕДИКАТЫ
};