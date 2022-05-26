#pragma once
#include "UserInterface.h"
#include "Alchemist.h"
#include "IngredientBuilder.h"

// Координаты
#define TITLE_Y_COORD					1		// Координаты Y курсора для печати названия программы
#define EXIT_Y_COORD					2		// Координата Y кнопки выхода
#define Y_COORD_AFTER_ALCHEMIST			8		// Координата Y после печати алхимика
#define MAIN_MENU_Y_COORD				9		// Координата Y меню действий
#define INSTRUCTIONS_Y_COORD			10
#define STANDARD_CURSOR_X_COORD			0		// Стандартная координата X курсора 


// Кол-ва
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// Кол-во пунктов в главном меню
#define NUMBER_OF_ALCHEMICAL_MENU_ITEMS	5		// Кол-во пунктов в алхимическом меню

class AlchemicalUserInterface : public UserInterface
{
public:

	// Конструктор по умолчанию
	AlchemicalUserInterface();

	// Запуск главного цикла программы
	void launchMainLoop() override;

private:

	// Коды меню
	enum MenuCode
	{
		MainMenu, 
		AlchemicalMenu,
		InstructionsMenu
	};

	// Коды пунктов в главном меню
	enum MainMenuCode
	{
		DoAlchemy = MAIN_MENU_Y_COORD,
		ReadInstructions
	};

	enum InstructionsMenuCode
	{
		Return = INSTRUCTIONS_Y_COORD,
		Exit
	};

	// Алхимик (пользователь)
	Alchemist* alchemist;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

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

	// Флаг для выхода из главного цикла
	bool exitFlag;

	// Координата X для инструкций
	int instructionsXCoord;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

	// Название инструкции
	string instructionsTitle;

	// Принять решение
	void chooseMenuItem(map <int, string> menu);

	// Сделать выбор пункта меню
	void makeChoice();

	// Проверка выбора в главном меню
	void checkChoiceInMainMenu();

	// Проверка выбора в меню инструкций
	void checkChoiceInInstructionsMenu();

	// Заниматься алхимией
	void doAlchemy();

	// Стирает с консоли все после печати алхимика
	void eraseScreenAfterAlchemist();

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	void printTitle() override;

	// Печатает "кнопку" выхода ESC
	void printExitButton() override;

	// Печать главного меню в цикле
	void printMenuInLoop(map <int, string> menu) override;

	// Печать инструкций
	void printInstructions() override;

	// Печатает меню действий
	void printActionMenu() override;

	// Печать прощания
	void printBye() override;

	// Печать инфы про алхимика
	void printAlchemist();

#pragma endregion МЕТОДЫ ПЕЧАТИ

};