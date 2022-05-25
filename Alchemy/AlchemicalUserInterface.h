#pragma once
#include "UserInterface.h"

class AlchemicalUserInterface : public UserInterface
{
public:

	// Конструктор по умолчанию
	AlchemicalUserInterface();

private:

};



// Класс - Пользовательский интерфейс
class UserInterface
{
public:

	// Конструктор по умолчанию
	UserInterface();

	//// Печать интерфейса
	//void print();

	// Цикл программы
	void mainloop();

	// задать название программы
	void setTitle(string title);

	// Сеттер для алхимика
	void setAlchemist(Alchemist* alchemist);

private:

	// Алхимик (пользователь)
	Alchemist* alchemist;

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	// Функция для предикатов
	function<bool(int)> func;

	// Ассоциативный массив координат и "кнопок меню"
	map <int, string> actionMenu;

	// Список строк - пунктов меню
	static string listOfMenuItems[TOTAL_NUMBER_OF_MENU_ITEMS];

#pragma region КООРДИНАТЫ

	// Координата Х - печати названия программы
	int titleXCoord;

	//int exitXCoord;

	// Текущая координата Х
	int currentXCursorCoord;

	// Текущая координата Y
	int currentYCursorCoord;

#pragma endregion КООРДИНАТЫ

	// Название программы
	string title;

	//// Нажатая пользователем клавиша
	//int key;

	// Экземпляр клавиатуры
	KeyBoard* keyBoard;

	// Расчитывает координату Х для заголовков
	void setXCoord();

	// Заполнить ассоциативный массив меню действий
	void fillActionMenuMap();

	//// Получение нажатой кнопки
	//void getKey();

	//// Проверка выбора в меню
	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);

	// Проверка выбора в меню
	void checkMenuChoice();

	// Проверка выбора стрелочек вверх/вниз
	void checkArrowsChoice(bool& exitFlag, int BorderYCoord, int keyCode);

	//// Проверить была ли команда покинуть программу
	//void checkExit();

	// Заниматься алхимией
	void doAlchemy();

#pragma region Методы печати

	// Печатает заголовок программы
	void printTitle();

	// Печать главного меню
	void printMainMenu();

	// Печать инструкций
	void printInstructions();

	//// Печать меню с вопросом о продолжении игры
	//void printContinueGameMenu();

	// Печатает меню действий
	void printActionMenu();

	// Печатает "кнопку" выхода ESC
	void printExitButton();

#pragma endregion Методы печати

	// Очищает на консоли всё, кроме названия программы
	void eraseScreenAfterTitle();




#pragma region ПРЕДИКАТЫ

	// Предикат для выбора пользователя в главном меню
	bool isMenuChoiceFalse(int key);

	// Предикат для выбора продолжения или создания игры
	bool isContinueGameFalse(int key);

	// Продолжить работу приложения или выйти
	bool isContinue(int key);

	// Не были ли нажаты кнопки стрелок?
	bool isArrowKeyFalse(int key);

#pragma endregion ПРЕДИКАТЫ


};

