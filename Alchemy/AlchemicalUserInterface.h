#pragma once
#include "UserInterface.h"
#include "Alchemist.h"
#include "IngredientBuilder.h"

//// Координаты
//#define MENU_Y_COORD					9		// Координата Y меню действий

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

	// Флаг для выхода из главного цикла
	bool exitFlag;

	// Принять решение
	void chooseMenuItem(map <int, string> menu);

	// Заниматься алхимией
	void doAlchemy();

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

	// Печать инфы про алхимика
	void printAlchemist();

#pragma endregion МЕТОДЫ ПЕЧАТИ

};