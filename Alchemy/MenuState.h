#pragma once
#include <string>
#include <iostream>
#include <map>
#include <functional>
#include "Formatting.h"
#include "ServiceFunctions.h"

using namespace std;

// Координаты
#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий
#define STANDARD_CURSOR_X_COORD			0		// Стандартная координата X курсора 
#define Y_COORD_AFTER_MENU_TITLE_1		9		// Координата Y первая после печати заголовка меню
#define Y_COORD_AFTER_MENU_TITLE_2		10		// Координата Y вторая после печати заголовка меню
#define Y_COORD_AFTER_MENU_TITLE_3		11		// Координата Y третья после печати заголовка меню
#define Y_COORD_AFTER_MENU_TITLE_4		12		// Координата Y четвертая после печати заголовка меню

class AlchemicalUserInterface;

class MenuState
{
public:
	
	// Конструктор по умолчанию
	MenuState();

	// Конструктор с параметром
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Конструктор копирования
	MenuState(MenuState const& copyMenuState);

	// Перегрузка оператора присваивания
	MenuState& operator = (MenuState const& right);

	// Деструктор
	virtual ~MenuState();

	// Задаем интерфейс
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать меню
	virtual void printMenu();

	//void fillMenuStates();

protected:

	// Экземпляр интерфейса
	AlchemicalUserInterface* alchemicalUserInterface;

	// Название меню
	string title;

	// Название меню при переходе в него
	string goToTitle;

	// текущая координата Y курсора 
	static int currentYCursorCoordState;

	// текущая координата X курсора 
	static int currentXCursorCoordState;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

	// кол-во состояний у данного состояния
	int numberOfStates;

	// Получить следующее состояние
	virtual MenuState* getNextState() = 0;

	// Задать список состояний
	virtual void setListOfStates() = 0;

	// Задать список создающих стейты функций
	virtual void setListOfCreatingFunctions() = 0;

	// Печать название меню
	virtual void printMenuTitle();

	// Печать главного меню
	virtual void printMenuItems();

	// Принять решение
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// Ассоциативный массив состояний
	std::map<int, MenuState*> menuStates;

	// Список состояний этого меню
	vector<MenuState*> listOfStates;

	// Проверка выбора стрелочек вверх/вниз
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

	// Очистить память
	virtual void clear();

private:

};