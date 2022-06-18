#pragma once
#include <string>
#include <iostream>
#include <map>
#include "Formatting.h"
//#include "AlchemicalUserInterface.h"

using namespace std;

// Кол-ва
#define NUMBER_OF_MAIN_MENU_ITEMS		2		// Кол-во пунктов в главном меню

// Координаты
#define MAIN_MENU_Y_COORD				10		// Координата Y меню действий

class AlchemicalUserInterface;

class MenuState
{
public:
	
	// Конструктор по умолчанию
	MenuState();

	// Конструктор с параметром
	MenuState(AlchemicalUserInterface* alchemicalUserInterface);

	// Деструктор
	virtual ~MenuState();

	// Задаем интерфейс
	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface);

	// Печать мееню
	virtual void printMenu();

protected:

	// Экземпляр интерфейса
	AlchemicalUserInterface* alchemicalUserInterface;

	// Название меню
	string title;

	// Название меню при переходе в него
	string goToTitle;

	static int currentYCursorCoordState;

	static int currentXCursorCoordState;

	// Граничная координата Y для управления стрелками
	int boundaryYCoord;

	// Флаг для выхода из главного цикла
	bool exitFlag;

	// Печать название меню
	virtual void printMenuTitle();

	// Печать главного меню
	virtual void printMenuItems();

	// Принять решение
	virtual void chooseMenuItem(/*map <int, string> menu*/);

	// Ассоциативный массив состояний
	std::map<int, MenuState*> menuStates;

	std::map<int, string> str;

	// Список состояний этого меню
	MenuState* listOfStates[NUMBER_OF_MAIN_MENU_ITEMS];

	// Задать список состояний
	virtual void setListOfStates() = 0;

	// Проверка выбора стрелочек вверх/вниз
	void checkVerticalArrowsChoice(int borderYCoord, int keyCode);

private:

};