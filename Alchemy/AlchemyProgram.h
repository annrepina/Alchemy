#pragma once
//#include <string>
//#include <conio.h>
//#include <functional>
//#include "Formatting.h"
//#include "KeyBoard.h"
#include "Alchemist.h"
//#include "EffectsTableBuilder.h"
#include "IngredientsTable.h"
#include "EffectsTable.h"

//using namespace std;
//
//using std::placeholders::_1;

//// Координаты
//#define TITLE_Y_COORD			1		// Координаты Y курсора для печати названия программы
//#define Y_COORD_AFTER_TITLE		4		// Координата Y после названя программы
//
//// Коды клавиш
//#define VK_1					0x31	// Клавиша 1
//#define VK_2					0x32	// Клавиша 2
//#define VK_NUMPAD1				0x61	// Клавиша цифровой клавиатуры 1
//#define VK_NUMPAD2				0x62	// Клавиша цифровой клавиатуры 2
//#define VK_ESCAPE				0x1B	// Клавиша ESC
//#define VK_RETURN				0x0D	// Клавиша Enter

class AlchemyProgram
{
public:

	// Конструктор по умолчанию
	AlchemyProgram();

#pragma region СЕТТЕРЫ

	// Сеттер для таблицы эффектов
	void setEffectsTable(EffectsTable* effectsTable);

	// Сеттер для таблицы ингредиентов
	void setIngredientsTable(IngredientsTable* ingredientsTable);

#pragma endregion СЕТТЕРЫ




#pragma region ГЕТТЕРЫ

	// Геттер для алхимика
	Alchemist* getAlchemist();

#pragma endregion ГЕТТЕРЫ

	//// Запуск главного цикла программы
	//void launchMainLoop();

private:

	// Алхимик (пользователь)
	Alchemist* alchemist;

	// Таблица эффектов
	EffectsTable* effectsTable;

	// Таблица ингредиентов
	IngredientsTable* ingredientsTable;

	//// Строитель таблицы эффектов
	//EffectsTableBuilder* effectsTableBuilder;



//	// Функция для предикатов
//	function<bool(int)> func;
//
//	// Координата Х - печати названия программы
//	int titleXCoord;
//
	//// Название программы
	//string title = "Зельеварение";
//
//	//// Нажатая пользователем клавиша
//	//int key;
//	
//	// Экземпляр клавиатуры
//	KeyBoard* keyBoard;
//
//	// Расчитывает координату Х для заголовков
//	void setXCoord();
//
//	//// Получение нажатой кнопки
//	//void getKey();
//
//	//// Проверка выбора в меню
//	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);
//
//	// Проверка выбора в меню
//	void checkMenuChoice();
//
//	// Заниматься алхимией
//	void doAlchemy();
//
//
//
//	// Печатает заголовок программы
//	void printTitle();
//
//	// Печать меню
//	void printMenu();
//
//	// Печать инструкций
//	void printInstructions();
//
//	// Очищает на консоли всё, кроме названия программы
//	void eraseScreenAfterTitle();
//
//
//
//#pragma region ПРЕДИКАТЫ
//
//	// Предикат для выбора пользователя в главном меню
//	bool isMenuChoiceFalse(int key);
//
//	// Предикат для выбора продолжения или создания игры
//	bool isContinueGameFalse(int key);
//
//	// Продолжить работу приложения или выйти
//	bool isContinue(int key);
//
//#pragma endregion ПРЕДИКАТЫ

};

