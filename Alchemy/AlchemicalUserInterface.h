#pragma once
#include "UserInterface.h"
//#include "Alchemist.h"
//#include "IngredientBuilder.h"
#include "AlchemyLogicBuilder.h"
#include "IngredientsTablePrinter.h"
#include "MainMenuState.h"
#include "IObserver.h"

// Координаты
#define TITLE_Y_COORD					1		// Координаты Y курсора для печати названия программы
#define EXIT_Y_COORD					2		// Координата Y кнопки выхода
#define Y_COORD_AFTER_ALCHEMIST			8		// Координата Y после печати алхимика
#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий
#define PAGE_Y_COORD					37		// Координата Y меню страниц таблицы
//#define Y_COORD_AFTER_MENU_TITLE_1		9		// Координата Y первая после печати заголовка меню
//#define Y_COORD_AFTER_MENU_TITLE_2		10		// Координата Y вторая после печати заголовка меню
//#define Y_COORD_AFTER_MENU_TITLE_3		11		// Координата Y третья после печати заголовка меню
//#define Y_COORD_AFTER_MENU_TITLE_4		12		// Координата Y четвертая после печати заголовка меню
//#define Y_COORD_AFTER_MENU_TITLE_4		12		// Координата Y четвертая после печати заголовка меню
//#define STANDARD_CURSOR_X_COORD			0		// Стандартная координата X курсора 


// Кол-ва
//#define NUMBER_OF_MAIN_MENU_ITEMS		2		// Кол-во пунктов в главном меню
//#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	7		// Кол-во пунктов в алхимическом меню
//#define NUMBER_OF_BUYING_MENU_ITEMS		3		// Кол-во пунктов в меню покупки ингредиентов

#define FIRST_PAGE						1		// Первая страница таблицы

#define MAX_INT							2147483647	// Самое большое число int 

#define TWO_LINES						2		// Две строчки

class AlchemicalUserInterface : public UserInterface
{
public:

	// Конструктор по умолчанию
	AlchemicalUserInterface();

	// Запуск главного цикла программы
	void launchMainLoop() override;

#pragma region ГЕТТЕРЫ

	// Получить граничную координату Y
	int getBoundaryYCoord();

	bool getExitFlag();

	AlchemyLogic* getAlchemyLogic();

#pragma endregion ГЕТТЕРЫ

#pragma region CЕТТЕРЫ

	// Установить состояние
	void setState(MenuState* state);

	void setExitFlag(bool exit);

#pragma endregion CЕТТЕРЫ

	enum TableCode
	{
		IngredientTable,
		PotionTable
	};

	// Печать страниц таблиц в цикле
	void printTablePagesInLoop(TableCode code, int& page);

	// Выбрать Id из таблицы
	int chooseId(string strChoice, TableCode code);

	// Вбрать кол-во ингредиента или зелья
	int chooseNumber(string strChoice, TableCode code, int yCoord);

	//// Попробовать добавить опр. кол-во ингредиента из списка
	//bool tryAddIngredientFromList(int id, int number);

private:

#pragma region КОДЫ

	//// Коды меню
	//enum MenuCode
	//{
	//	MainMenu1, 
	//	AlchemicalMenu,
	//	InstructionsMenu,
	//	BuyingIngredientsMenu,
	//	BuyingFaultMenu
	//};

	//// Коды пунктов в главном меню
	//enum MainMenuCode
	//{
	//	DoAlchemy = MAIN_MENU_Y_COORD,
	//	ReadInstructions
	//};

	//// Коды алхимического меню
	//enum AlchemicalMenuCode
	//{
	//	MakingPotions = MAIN_MENU_Y_COORD,
	//	BuyingIngredients,
	//	SellingIngredients,
	//	EatingIngredients,
	//	SellingPotions,
	//	WorkingWithTables, 
	//	AlcReturn
	//};

	//// Коды меню инструкций
	//enum InstructionsMenuCode
	//{
	//	InstrReturn = MAIN_MENU_Y_COORD,
	//	Exit
	//};

	//// Коды меню покупки ингредиентов
	//enum BuyingIngredientsMenuCode 
	//{
	//	ChooseFromList = MAIN_MENU_Y_COORD,
	//	CreateNewIngredient
	//};

	//// Коды меню ошибки во время покупки ингредиентов
	//enum BuyingFaultMenuCode
	//{
	//	СhooseAnotherIngredient = MAIN_MENU_Y_COORD, 
	//	ChangeNumberOfIngredient
	//};



#pragma endregion 

	// Программа - алхимия
	AlchemyLogic* alchemyLogic;

	// Строитель для алхимической программы
	AlchemyLogicBuilder* alchemyLogicBuilder;

	// Парсер для программы алхимии
	AlchemyProgramParser* alchemyProgramParser;

	// Принтер для печати таблицы ингредиентов
	IngredientsTablePrinter* ingredientsTableprinter;

	// Состояние меню
	MenuState* state;

	// Настроить программу Алхимии
	void setAlchemyLogic();

	//// Список строк - пунктов главного меню
	//static string listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// Ассоциативный массив координат и "кнопок" главного меню
	//map <int, string> mainMenu;

	//// Список строк - пунктов меню алхимии
	//static string listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS];

	//// Ассоциативный массив координат и "кнопок" меню алхимии
	//map <int, string> alchemicalMenu;

	//// Список строк - пунктов меню инструкций
	//static string listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// Ассоциативный массив координат и "кнопок" меню инструкций
	//map <int, string> instructionsMenu;

	//// Список строк - пунктов меню покупки ингредиентов
	//static string listOfBuyingIngredientsMenuItems[NUMBER_OF_BUYING_MENU_ITEMS];
	//
	//// Ассоциативный массив координат и "кнопок" меню покупки ингредиентов
	//map<int, string> buyingIngredientsMenu;

	//// Список строк - пунктов меню ошибки при покупке ингредиентов
	//static string listOfBuyingFaultMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	//// Ассоциативный массив координат и пунктов меню ошибки во время покупки ингредиентов
	//map <int, string> buyingFaultMenu;

	// Флаг для выхода из главного цикла
	bool exitFlag;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

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

	//// Принять решение
	//void chooseMenuItem(map <int, string> menu);

	// Выбрать страницу таблицы
	void choosePage(int page, TableCode code);

	//// Сделать выбор пункта меню
	//void makeChoice(bool& innerExitFlag);

	//void makeChoice();

#pragma region ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

	//// Проверка выбора в главном меню
	//void checkMainMenu(bool& innerExitFlag);

	//// Проверка выбора в меню инструкций
	//void checkInstructionsMenu(bool& innerExitFlag);

	//// Проверка выбоа меню в меню алхимии
	//void checkAlchemicalMenu(bool& innerExitFlag);

	//// Проверка выбора пункта в меню покупки ингредиентов
	//void checkBuyingIngredientsMenu(bool& innerExitFlag);

	//// Проверка выбора пункта в меню ошибки при покупки ингредиентов из списка 
	//void checkBuyingFaultMenu();

	// Проверить горизонтальные стрелки
	bool checkHorizontalArrowChoice(int& page, TableCode code, int keyCode);

#pragma endregion ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

	//// Заниматься алхимией
	//void doAlchemy();

	//// Покупка ингредиентов
	//void buyIngredients();

	//// Покупка ингредиентов из имеющегося списка
	//void buyIngredientsFromList();

	// Стирает с консоли все после печати алхимика
	void eraseScreenAfterAlchemist();

	//// Заполнить все меню
	//void fillAllMenu();

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	void printTitle() override;

	// Печатает "кнопку" выхода ESC
	void printExitButton() override;

	// Печать главного меню в цикле
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	//// Печать инструкций
	//void printInstructions() override;

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

#pragma endregion ПРЕДИКАТЫ

};