#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "KeyBoard.h"

using namespace std;

using std::placeholders::_1;

// Координаты
#define TITLE_Y_COORD			1		// Координаты Y курсора для печати названия программы
#define Y_COORD_AFTER_TITLE		4		// Координата Y после названя программы

#define EXIT_Y_COORD			2		// Координата Y кнопки выхода

#define MENU_Y_COORD			9		// Координата Y меню действий

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

	// Название программы
	string title;

	// Функция для предикатов
	function<bool(int)> func;

	// Экземпляр клавиатуры
	KeyBoard* keyBoard;

	// Заполнить ассоциативный массив меню действий
	virtual void fillActionMenuMap(const int menuYCoord, const int numberOfItems, const string listOfItems[], map <int, string> menu);

	// Проверка выбора в меню
	void checkMenuChoice();

	// Проверка выбора стрелочек вверх/вниз
	void checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode, map <int, string> actionMenu);

	// Очищает на консоли всё, кроме названия программы
	void eraseScreenAfterTitle();

	// Расчитывает координату Х для заголовков
	void setXCoord();

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	virtual void printTitle() = 0;

	// Печатает "кнопку" выхода ESC
	virtual void printExitButton() = 0;

	// Печать главного меню
	virtual void printMainMenu() = 0;

	// Печать инструкций
	virtual void printInstructions() = 0;

	// Печатает меню действий
	virtual void printActionMenu() = 0;

#pragma endregion МЕТОДЫ ПЕЧАТИ

#pragma region ПРЕДИКАТЫ

	// Предикат для выбора пользователя в главном меню
	bool isMenuChoiceFalse(int key);

	// Не были ли нажаты кнопки стрелок?
	bool isArrowKeyFalse(int key);

#pragma endregion ПРЕДИКАТЫ

#pragma region КООРДИНАТЫ

	// Координата Х - печати названия программы
	int titleXCoord;

	// Текущая координата Х
	int currentXCursorCoord;

	// Текущая координата Y
	int currentYCursorCoord;

#pragma endregion КООРДИНАТЫ

private:

};

