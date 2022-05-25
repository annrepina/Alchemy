#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "KeyBoard.h"
#include "IngredientBuilder.h"

using namespace std;

using std::placeholders::_1;

// Координаты
#define TITLE_Y_COORD			1		// Координаты Y курсора для печати названия программы
#define Y_COORD_AFTER_TITLE		4		// Координата Y после названя программы
#define ACTION_MENU_Y_COORD		8		// Координата Y меню действий
#define EXIT_Y_COORD			2		// Координата Y кнопки выхода

// Коды клавиш
#define VK_1					0x31	// Клавиша 1
#define VK_2					0x32	// Клавиша 2
#define VK_NUMPAD1				0x61	// Клавиша цифровой клавиатуры 1
#define VK_NUMPAD2				0x62	// Клавиша цифровой клавиатуры 2
#define VK_ESCAPE				0x1B	// Клавиша ESC
#define VK_RETURN				0x0D	// Клавиша Enter
#define VK_LEFT					75		// Клавиша со стрелкой влево
#define VK_UP					72		// Клавиша со стрелкой вверх
#define VK_RIGHT				77		// Клавиша со стрелкой вправо
#define VK_DOWN					80		// Клавиша со стрелкой вниз


#define NUMBER_OF_MAIN_MENU_ITEMS	6		// Количество главных пунктов меню в интерфейсе вместе с "выберите"


// Класс - Пользовательский интерфейс
class UserInterface
{
public:

	// Конструктор по умолчанию
	UserInterface();

	// Цикл программы
	virtual void launchMainLoop() = 0;

	// задать название программы
	void setTitle(string title);

protected:

	// Функция для предикатов
	function<bool(int)> func;

	// Экземпляр клавиатуры
	KeyBoard* keyBoard;

	// Ассоциативный массив координат и "кнопок меню"
	map <int, string> actionMenu;

	// Заполнить ассоциативный массив меню действий
	virtual void fillActionMenuMap() = 0;

	// Проверка выбора в меню
	void checkMenuChoice();

	// Проверка выбора стрелочек вверх/вниз
	void checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode);

	// Очищает на консоли всё, кроме названия программы
	void eraseScreenAfterTitle();

#pragma region Методы печати

	// Печатает заголовок программы
	virtual void printTitle() = 0;

	// Печатает "кнопку" выхода ESC
	virtual void printExitButton() = 0;

	// Печать главного меню
	virtual void printMainMenu() = 0;

	// Печать инструкций
	virtual void printInstructions() = 0;

#pragma endregion Методы печати

#pragma region Предикаты

	// Предикат для выбора пользователя в главном меню
	bool isMenuChoiceFalse(int key);

#pragma endregion Предикаты

private:

#pragma region КООРДИНАТЫ

	// Координата Х - печати названия программы
	int titleXCoord;

	// Текущая координата Х
	int currentXCursorCoord;

	// Текущая координата Y
	int currentYCursorCoord;

#pragma endregion КООРДИНАТЫ

	// Название программы
	string title;

	// Расчитывает координату Х для заголовков
	void setXCoord();


	//// Проверка выбора в меню
	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);






#pragma region Методы печати

	//// Печать главного меню
	//void printMainMenu();



	//// Печать меню с вопросом о продолжении игры
	//void printContinueGameMenu();

	// Печатает меню действий
	void printActionMenu();

#pragma endregion Методы печати






#pragma region ПРЕДИКАТЫ



	// Предикат для выбора продолжения или создания игры
	bool isContinueGameFalse(int key);

	// Продолжить работу приложения или выйти
	bool isContinue(int key);

	// Не были ли нажаты кнопки стрелок?
	bool isArrowKeyFalse(int key);

#pragma endregion ПРЕДИКАТЫ


};

