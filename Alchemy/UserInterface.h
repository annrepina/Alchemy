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
#define Y_COORD_AFTER_TITLE				4		// Координата Y после названя программы
#define Y_COORD_AFTER_MENU_TITLE		9		// Координата Y после печати заголовка меню

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
	void setTitle(const string title);

protected:

	// Название программы
	string title;

	// Функция для предикатов
	function<bool(int)> func;

	// Экземпляр клавиатуры
	KeyBoard* keyBoard;

	// Код меню
	int menuCode;

	// Заполнить ассоциативный массив меню действий
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[]);

	// Проверка выбора в меню
	void checkMenuChoice() const;

	// Проверка выбора стрелочек вверх/вниз
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode, map <int, string> menu);

	// Очищает на консоли всё, кроме названия программы
	void eraseScreenAfterTitle() const;

	// Проверка ввода
	void checkInput(int& value, int min, int max, string strChoice);

	//// Расчитывает координату Х для заголовков
	//void setXCoordInMiddle();

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	virtual void printTitle() = 0;

	// Печатает "кнопку" выхода ESC
	virtual void printExitButton() = 0;

	// Печать главного меню
	virtual void printMenu(map <int, string> menu) const;

	// Печать главного меню в цикле
	virtual void printMenuInLoop(map<int, string> menu, string menuTitle) = 0;

	// Печать инструкций
	virtual void printInstructions() = 0;

	// Печать прощания
	virtual void printBye() = 0;

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

