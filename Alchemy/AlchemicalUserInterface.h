#pragma once
#include "UserInterface.h"
//#include "Alchemist.h"
//#include "IngredientBuilder.h"
#include "AlchemyProgramBuilder.h"
#include "IngredientsTablePrinter.h"
//#include "AlchemyProgram.h"

// Координаты
#define TITLE_Y_COORD					1		// Координаты Y курсора для печати названия программы
#define EXIT_Y_COORD					2		// Координата Y кнопки выхода
#define Y_COORD_AFTER_ALCHEMIST			8		// Координата Y после печати алхимика
#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий
//#define INSTRUCTIONS_Y_COORD			10
#define Y_COORD_AFTER_MENU_TITLE		9		// Координата Y после печати заголовка меню
#define STANDARD_CURSOR_X_COORD			0		// Стандартная координата X курсора 



// Кол-ва
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// Кол-во пунктов в главном меню
#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	6		// Кол-во пунктов в алхимическом меню

#define FIRST_PAGE						1		// Первая страница таблицы

class AlchemicalUserInterface : public UserInterface
{
public:

	// Конструктор по умолчанию
	AlchemicalUserInterface();

	// Запуск главного цикла программы
	void launchMainLoop() override;

private:

#pragma region КОДЫ

	// Коды меню
	enum MenuCode
	{
		MainMenu, 
		AlchemicalMenu,
		InstructionsMenu,
		BuyingIngredientsMenu
	};

	// Коды пунктов в главном меню
	enum MainMenuCode
	{
		DoAlchemy = MAIN_MENU_Y_COORD,
		ReadInstructions
	};

	// Коды алхимического меню
	enum AlchemicalMenuCode
	{
		MakingPotions = MAIN_MENU_Y_COORD,
		BuyingIngredients,
		SellingIngredients,
		EatingIngredients,
		SellingPotions,
		WorkingWithTables
	};

	// Коды меню инструкций
	enum InstructionsMenuCode
	{
		Return = MAIN_MENU_Y_COORD,
		Exit
	};

	// Коды меню покупки ингредиентов
	enum BuyingIngredientsMenuCode 
	{
		ChooseFromList = MAIN_MENU_Y_COORD,
		CreateNewIngredient
	};

	enum TableCode
	{
		IngredientsTable,
		PotionsTable
	};

#pragma endregion 

	// Программа - алхимия
	AlchemyProgram* alchemyProgram;

	// Строитель для алхимической программы
	AlchemyProgramBuilder* alchemyProgramBuilder;

	// Парсер для программы алхимии
	AlchemyProgramParser* alchemyProgramParser;

	// Принтер для печати таблицы ингредиентов
	IngredientsTablePrinter* ingredientsTableprinter;

	// Настроить программу Алхимии
	void setAlchemyProgram();

	// Алхимик (пользователь)
	//Alchemist* alchemist;

	//// Строитель ингредиентов
	//IngredientBuilder* ingredientBuilder;

	// Список строк - пунктов главного меню
	static string listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	// Ассоциативный массив координат и "кнопок" главного меню
	map <int, string> mainMenu;

	// Список строк - пунктов меню алхимии
	static string listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS];

	// Ассоциативный массив координат и "кнопок" меню алхимии
	map <int, string> alchemicalMenu;

	// Список строк - пунктов меню инструкций
	static string listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];

	// Ассоциативный массив координат и "кнопок" меню инструкций
	map <int, string> instructionsMenu;

	// Список строк - пунктов меню покупки ингредиентов
	static string listOfBuyingIngredientsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS];
	
	// Ассоциативный массив координат и "кнопок" меню покупки ингредиентов
	map<int, string> buyingIngredientsMenu;

	// Флаг для выхода из главного цикла
	bool exitFlag;

	//// Координата X для инструкций
	//int instructionsXCoord;

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

#pragma endregion НАЗВАНИЕ ЗАГОЛОВКОВ

	// Принять решение
	void chooseMenuItem(map <int, string> menu);

	// Выбрать страницу таблицы
	void choosePage(int page, TableCode code);

	// Выбрать Id из таблицы
	int chooseId(string strChoice, TableCode code);

	// Сделать выбор пункта меню
	void makeChoice();

#pragma region ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

	// Проверка выбора в главном меню
	void checkMainMenu();

	// Проверка выбора в меню инструкций
	void checkInstructionsMenu();

	// Проверка выбоа меню в меню алхимии
	void checkAlchemicalMenu();

	// Проверка выбора пункта в меню покупки ингредиентов
	void checkBuyingIngredientsMenu();

	// Проверить горизонтальные стрелки
	bool checkHorizontalArrowChoice(int& page, TableCode code, int keyCode);

#pragma endregion ПРОВЕРКА МЕНЮ ИЛИ ВЫБОРА

	// Заниматься алхимией
	void doAlchemy();

	// Покупка ингредиентов
	void buyIngredients();

	// Покупка ингредиентов из имеющегося списка
	void buyIngredientsFromList();

	// Стирает с консоли все после печати алхимика
	void eraseScreenAfterAlchemist();

	// Заполнить все меню
	void fillAllMenu();

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	void printTitle() override;

	// Печатает "кнопку" выхода ESC
	void printExitButton() override;

	// Печать главного меню в цикле
	void printMenuInLoop(map<int, string> menu, string menuTitle) override;

	// Печать инструкций
	void printInstructions() override;

	// Печать прощания
	void printBye() override;

	// Печать инфы про алхимика
	void printAlchemist();

	// Печать названия Меню
	void printMenuTitle(string title);

	// Печать меню выбора страницы
	void printPageMenu(int page);

	// Печать страниц таблиц в цикле
	void printTablePagesInLoop(TableCode code, int& page);

#pragma endregion МЕТОДЫ ПЕЧАТИ

#pragma region ПРЕДИКАТЫ

	// Неправилный выбор страницы
	bool isPageChoiceFalse(int key);

#pragma endregion ПРЕДИКАТЫ

};