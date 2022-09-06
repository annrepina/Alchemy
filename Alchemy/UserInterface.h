#pragma once
#include <string>
#include <conio.h>
#include <functional>
#include <map>
#include "Formatting.h"
#include "ServiceFunctions.h"
#include "KeyBoard.h"
//#include "MenuState.h"
//#include "MenuState.h"

using namespace std;

using std::placeholders::_1;

#define MAX_INT							2147483647	// Самое большое число int 

// Координаты
#define Y_COORD_AFTER_TITLE				4		// Координата Y после названя программы
#define Y_COORD_AFTER_MENU_TITLE_1		9		// Координата Y после печати заголовка меню

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

#define EXIT_INT					-1		// Значения int в случае выхода


// Класс - Пользовательский интерфейс
class UserInterface
{
public:

	// Конструктор по умолчанию
	UserInterface();

	// Цикл программы
	virtual void launchMainLoop() = 0;

	// Функция для предикатов
	function<bool(int)> func;

#pragma region СЕТТЕРЫ

	// задать название программы
	void setTitle(const string title);

	// Сеттер для текущей координаты Y
	void setCurrentYCursorCoord(int yCoord);

	// Сеттер для функции
	void setFunc(function<bool(int)> func);

#pragma endregion СЕТТЕРЫ

#pragma region ГЕТТЕРЫ

	// Геттер для получения текущей координаты Y
	int getCurrentYCursorCoord();

	// Геттер для получения текущей координаты X
	int getCurrentXCursorCoord();

	// Получить функцию
	function<bool(int)> getFunc();

	// Получить клаву
	KeyBoard* getKeyBoard();

#pragma endregion ГЕТТЕРЫ

#pragma region ПРЕДИКАТЫ

	// Не были ли нажаты кнопки стрелок?
	bool isArrowKeyFalse(int key);

	// Была ли нажата клавиша выхода?
	virtual bool isEscKeyPressed();

	// Была ли нажата клавиша выхода?
	virtual bool isEscKeyFalse(int key);

	// Не были нажаты Enter и Esc
	bool isEnterEscKeyFalse(int key);

#pragma endregion ПРЕДИКАТЫ

	// Проверка выбора в меню
	void checkMenuChoice() const;

	// Проверка ввода
	virtual string checkInput(string& value, bool isString, int max, int min, int yCoord, int xCoord);

	// Печать ошибки из-за некорректного ввода
	virtual void printError(int yCoord, int xCoord, string textOfError);

protected:

	// Название программы
	string title;

	// Экземпляр клавиатуры
	KeyBoard* keyBoard;

	//// Код меню
	//int menuCode;

	// Заполнить ассоциативный массив меню действий
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[]);

	// Пергегрузка функции заполнения ассоциативного масссива с координатами
	virtual map<int, string> fillMenuMap(const int numberOfItems, const string listOfItems[], int yCoord);

	// Очищает на консоли всё, кроме названия программы
	void eraseScreenAfterTitle() const;

	// Проверка ввода
	int checkInput(string value, int min, int max, string textOfRangeError, int yCoord, int xCoord);

#pragma region МЕТОДЫ ПЕЧАТИ

	// Печатает заголовок программы
	virtual void printTitle() = 0;

	// Печатает "кнопку" выхода ESC
	virtual void printExitButton() = 0;

	// Печать главного меню
	virtual void printMenu(map <int, string> menu) const;

	// Печать главного меню в цикле
	virtual void printMenuInLoop(map<int, string> menu, string menuTitle) = 0;

	// Печать прощания
	virtual void printBye() = 0;

#pragma endregion МЕТОДЫ ПЕЧАТИ

	// Координата Х - печати названия программы
	int titleXCoord;

	// Текущая координата Х
	int currentXCursorCoord;

	// Текущая координата Y
	int currentYCursorCoord;

private:

};

